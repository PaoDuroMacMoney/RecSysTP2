#include "ColaborativeSolver.h"

#include <iostream>
#include <algorithm>   
#include <math.h>
#include <cfloat>
#include <sstream>

bool descendingSimilarityOrder(neighboor * i, neighboor * j)
{
	return i->similarity > j->similarity;
}

ColaborativeParameters * ColaborativeSolver::getParams()
{
	return (ColaborativeParameters *)parameters;
}

void ColaborativeSolver::beforePredict()
{
	input->normalizeUsers(getParams()->normalizer);
}

void ColaborativeSolver::afterPredict()
{
	input->denormalizeUsers(getParams()->normalizer);
}

ColaborativeSolver::ColaborativeSolver(data_input * input, Parameters * params)
	: GenericSolver(input, params)
{
	neighboors = new unordered_map<string, neighboor *>;
}

vector<neighboor *> ColaborativeSolver::getUserNeighboors(data_input * input, string mainDimensionId, string auxDimensionId)
{
	if (lastCalculated != mainDimensionId)
	{
		for (auto iterator = neighboors->begin(); iterator != neighboors->end(); iterator++)
		{
			delete iterator->second;
		}
		neighboors->clear();
		lastCalculated = mainDimensionId;

		vector<data_node *> * mainDimensionRates = getMainDimensionFunc(mainDimensionId);
 		for (unsigned int i = 0; i < mainDimensionRates->size(); i++)
		{
			//como j� est� tudo normalizado o c�lculo da similaridade de pearson pode ser simplificado, todos
			//os termos de m�dia ser�o 0, e fica equivalente com o cosseno.
			data_node * mainDimensionNode = (*mainDimensionRates)[i];
			float targetRate = mainDimensionNode->value;
			string auxDimensionId = chooseAuxDimension(mainDimensionNode->userId,
				mainDimensionNode->itemId);

			vector<data_node *> * auxDimensionRates = getAuxDimensionFunc(auxDimensionId);
			for (unsigned int j = 0; j < auxDimensionRates->size(); j++)
			{				
				data_node * auxDimensionNode = (*auxDimensionRates)[j];
				string neighboorId = chooseMainDimension(auxDimensionNode->userId,
					auxDimensionNode->itemId);
				float neighboorRate = auxDimensionNode->value;
				if (neighboorId != mainDimensionId && neighboorRate != 0 && targetRate != 0)
				{
					updateNeighboorhood(neighboors, neighboorId, targetRate, neighboorRate);
				}
			}
		}

		for (auto iterator = neighboors->begin(); iterator != neighboors->end(); iterator++)
		{
			neighboor * neighboor = iterator->second;
			neighboor->similarity = neighboor->numeratorTemp / (sqrt(neighboor->denominatorTemp1)*sqrt(neighboor->denominatorTemp2));
			float cost = std::min((float)(neighboor->commonRates) / 50.0f, 1.0f);
			neighboor->similarity *= cost;
		}
	}

	for (auto iterator = neighboors->begin(); iterator != neighboors->end(); iterator++)
	{
		iterator->second->value = FLT_MIN;
	}

	auto list = getAuxDimensionFunc(auxDimensionId);
	for (unsigned int i = 0; i < list->size(); i++)
	{
		string key = chooseMainDimension(list->at(i)->userId, list->at(i)->itemId);
		auto iterator = neighboors->find(key);
		if (iterator != neighboors->end())
		{
			iterator->second->value = list->at(i)->value;
		}
	}

	vector<neighboor *> result;
	for (auto iterator = neighboors->begin(); iterator != neighboors->end(); iterator++)
	{
		neighboor * neighboor = iterator->second;
		if (neighboor->value != FLT_MIN)
		{
			result.push_back(neighboor);
		}
	}

	std::sort(result.begin(), result.end(), descendingSimilarityOrder);
	return result;
}

void ColaborativeSolver::updateNeighboorhood(unordered_map<string, neighboor *>* neighboors,
	string neighboorId, float targetRating, float neighboorRate)
{
	neighboor * neighboorToUpdate;
	auto iterator = neighboors->find(neighboorId);
	if (iterator == neighboors->end())
	{
		neighboorToUpdate = new neighboor;
		neighboorToUpdate->neighboorId = neighboorId;
		neighboors->insert(pair<string, neighboor *>(neighboorId, neighboorToUpdate));
	}
	else
	{
		neighboorToUpdate = iterator->second;
	}

	neighboorToUpdate->numeratorTemp += (targetRating*neighboorRate);
	neighboorToUpdate->denominatorTemp1 += (targetRating*targetRating);
	neighboorToUpdate->denominatorTemp2 += (neighboorRate*neighboorRate);

	neighboorToUpdate->commonRates++;
}

float ColaborativeSolver::predict(string targetUser, string targetItem)
{
	float blindGuess = getBlindGuess(targetUser, targetItem);
	if (blindGuess != 0)
	{
		//o usu�rio n�o tem avalia��es chute ser� a m�dia para o item, 
		//caso o item n�o tenha avalia��es o chute ser� a m�dia global.
		return blindGuess;
	}
	string mainDimensionId = chooseMainDimension(targetUser, targetItem);
	string auxDimensionId = chooseAuxDimension(targetUser, targetItem);

	vector<neighboor*> neighboors = getUserNeighboors(input, mainDimensionId, auxDimensionId);
	if (neighboors.size() == 0)
	{
		//item n�o tem avalia��es, ou itens que o usu�rio avaliou n�o t�m vizinhan�a, 
		//o chute ser� a m�dia do usu�rio
		return input->userInfo[targetUser]->getAverage();
	}
	float score = 0, normalizeFactor = 0;

	int neighboorsLimit = std::min((int)neighboors.size(), getParams()->neighboors);

	for (int i = 0; i < neighboorsLimit; i++)
	{
		neighboor * item = neighboors[i];
		score += item->similarity * item->value;
		normalizeFactor += std::abs(item->similarity);
	}

	float accuracyThreshold = getParams()->accuracyThreshold;

	for (unsigned int i = neighboorsLimit; i < neighboors.size(); i++)
	{
		neighboor * item = neighboors[i];
		if (item->similarity > accuracyThreshold)
		{
			score += item->similarity * item->value;
			normalizeFactor += std::abs(item->similarity);
		}
	}

	score = score / normalizeFactor;

	float result = input->userInfo[targetUser]->denormalize(score, getParams()->normalizer);
	float minLimit = input->userInfo[targetUser]->getMin();
	float maxLimit = input->userInfo[targetUser]->getMax();
	float prediction = std::min(maxLimit, std::max(minLimit, result));
	return prediction;
}

ColaborativeParameters::ColaborativeParameters(int neighboorsAmount, float accuracyThresholdValue, Normalizer * normalizationStrategy)
{
	update(neighboorsAmount, accuracyThresholdValue, normalizationStrategy);
}

void ColaborativeParameters::update(int neighboorsAmount, float accuracyThresholdValue, Normalizer * normalizationStrategy)
{
	neighboors = neighboorsAmount;
	accuracyThreshold = accuracyThresholdValue;
	normalizer = normalizationStrategy;
}

string ColaborativeParameters::print()
{
	std::stringstream stream;
	stream << getAlgorithmName()<< " "<<normalizer->getName() <<" neighboors: " << neighboors << "  accuracy Threshold: " << accuracyThreshold;
	return stream.str();
}
