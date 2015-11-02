#include "ColaborativeItemBasedSolver.h"
#include <iostream>
#include <algorithm>   
#include <math.h>
#include <sstream>

ColaborativeItemBasedSolver::ColaborativeItemBasedSolver(data_input * input, Parameters * params)
	: ColaborativeSolver(input, params)
{
}

string ColaborativeItemBasedSolver::chooseMainDimension(string userId, string itemId)
{
	return itemId;
}

string ColaborativeItemBasedSolver::chooseAuxDimension(string userId, string itemId)
{
	return userId;
}

vector<data_node*> * ColaborativeItemBasedSolver::getMainDimensionFunc(string dimensionId)
{
	return &input->itemInfo[dimensionId]->ratedList;
}

vector<data_node*> * ColaborativeItemBasedSolver::getAuxDimensionFunc(string dimensionId)
{
	return &input->userInfo[dimensionId]->ratedList;
}

bool ColaborativeItemBasedSolver::sortBeforeSolveFunc(data_node i, data_node j)
{
	return i.itemId < j.itemId;
}

ColaborativeItemBasedParameters::ColaborativeItemBasedParameters(int neighboorsAmount, float accuracyThresholdValue, Normalizer * normalizationStrategy)
	:ColaborativeParameters(neighboorsAmount, accuracyThresholdValue, normalizationStrategy)
{
}

string ColaborativeItemBasedParameters::getAlgorithmName()
{
	return "ItemBased";
}
