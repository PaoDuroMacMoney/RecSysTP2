// Netflix.cpp : Defines the entry point for the console application.
//

#include "Util.h"
#include "Solver.h"
#include "ColaborativeItemBasedSolver.h"
#include "ColaborativeUserBasedSolver.h"
#include "CrossValidation.h"
#include <iostream>
using namespace std;


int main()
{
	data_input * input = read_input("ratings.csv");
	data_input * target = read_input("targets.csv", true);

	ColaborativeUserBasedParameters * params = new ColaborativeUserBasedParameters(1, 0, new ZScoreNormalizer);
	ColaborativeUserBasedSolver * solver = new ColaborativeUserBasedSolver(input, params);

	solver->solve(target);
	//CrossValidation * crossValidation = new CrossValidation(5, input, solver);

	//params->update(33, 0, new ZScoreNormalizer);
	//crossValidation->run();

	//params->update(1, 0, new ZScoreNormalizer);
	//crossValidation->run();
	std::cout<<"Press any key to exit";
	getchar();

	return 0;
}

