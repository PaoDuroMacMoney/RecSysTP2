#pragma once
#include "Solver.h"
#include <unordered_map>

class ColaborativeParameters : public Parameters
{
public:
	ColaborativeParameters(int neighboorsAmount, float accuracyThresholdValue, Normalizer * normalizationStrategy);
	void update(int neighboorsAmount, float accuracyThresholdValue, Normalizer * normalizationStrategy);
	string print() override;
public:
	float accuracyThreshold = 0.0f;
	int neighboors = 1000;
	Normalizer * normalizer;
};

class ColaborativeSolver : public GenericSolver
{
private:
	string lastCalculated = "";
public:
	unordered_map<string, neighboor *> * neighboors;// = new unordered_map<string, neighboor *>;
	virtual string chooseMainDimension(string userId, string itemId) = 0;
	virtual string chooseAuxDimension(string userId, string itemId) = 0;
	virtual vector<data_node*> * getMainDimensionFunc(string dimensionId) =0;
	virtual vector<data_node*> * getAuxDimensionFunc(string dimensionId) =0;

	virtual void beforePredict() override;
	virtual void afterPredict() override;
	ColaborativeSolver(data_input * input, Parameters * params);
	vector<neighboor *> getUserNeighboors(data_input * input, string mainDimensionId, string auxDimensionId);
	void updateNeighboorhood(unordered_map<string, neighboor *> * neighboors, string neighboorId, float targetRating, float neighboorRate);
	virtual float predict(string targetUser, string targetItem) override;
	ColaborativeParameters * getParams();
};

bool descendingSimilarityOrder(neighboor * i, neighboor * j);
