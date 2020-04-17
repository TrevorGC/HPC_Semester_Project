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
		void mate(individual parent2, string TARGET, individual& offspring);
		int cal_fitness(string TARGET);
		string getChromosome();
		int getFitness();
};

#endif