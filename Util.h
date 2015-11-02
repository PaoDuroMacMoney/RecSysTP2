#pragma once
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Normalizer
{
public:
	virtual float calc(float originalValue, float average, float standardDeviation, float minValue, float maxValue) = 0;
	virtual float undo(float normalizedValue, float average, float standardDeviation, float minValue, float maxValue) = 0;
	virtual string getName() = 0;
	virtual ~Normalizer(){}
};

class ZScoreNormalizer :public Normalizer
{
	virtual float calc(float originalValue, float average, float standardDeviation, float minValue, float maxValue) override;
	virtual float undo(float normalizedValue, float average, float standardDeviation, float minValue, float maxValue) override;
	virtual string getName() override;
};

class MaxMinNormalizer :public Normalizer
{
	virtual float calc(float originalValue, float average, float standardDeviation, float minValue, float maxValue) override;
	virtual float undo(float normalizedValue, float average, float standardDeviation, float minValue, float maxValue) override;

	// Inherited via Normalizer
	virtual string getName() override;
};

struct data_node
{
	string userId;
	string itemId;
	int timestamp;
	float value;
};

class neighboor
{
public:
	string neighboorId;
	float numeratorTemp =0;
	float denominatorTemp1 =0;
	float denominatorTemp2 =0;
	float similarity =0;
	float value =0;
	int commonRates =0;
};

class data_info
{
public:
	float getAverage();
	float getStdDeviation();
	float getMax();
	float getMin();
	void resetValues();
	void normalize(Normalizer * normalizer);
	void denormalize(Normalizer * normalizer);
	void updateMaxMin(float value);
	float denormalize(float score, Normalizer * normalizer);
	int count =0;
	vector<data_node*> ratedList;
private:
	float min = 10;
	float max = 1;
	float average = 0;
	float std_deviation=-1;
};

class data_input
{
	friend std::istream & operator>>(std::istream & stream, data_input & input);

public:
	void normalizeUsers(Normalizer * normalizer);
	void denormalizeUsers(Normalizer * normalizer);
	unordered_map <string, data_info *> userInfo;
	unordered_map <string, data_info *> itemInfo;
	int length;
	data_node * data;
	bool isTarget;
	int insertIndex;
	float generalAverage =0;
};

data_input * read_input(char const * path, bool isTarget = false);

void loadMap(unordered_map<string, data_info *> * map, string key, data_node * node);
void readAsTarget(std::istream & stream, data_input & input);
void readAsInput(std::istream & stream, data_input & input);
data_input * select_input(data_input * completeInput, vector<int> * allButFolder);
