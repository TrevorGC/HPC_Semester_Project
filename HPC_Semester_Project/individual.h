#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class individual
{
private:
	string chromosome;
	int fitness;

public:
	individual();
	individual(string chromosome, string TARGET);

	individual mate(individual parent2, string TARGET);

	void next_Generation(int start, int end, vector<individual> population, string TARGET, vector<individual>& newGeneration);

	int cal_fitness(string TARGET);
	string getChromosome();
	int getFitness();
};

#endif