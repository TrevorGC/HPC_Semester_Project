#include <iostream>
#include "genetic_math.h"
#include "individual.h"
#include "stdio.h"
#include <chrono> 
using namespace std::chrono;
using namespace std;

// Number of individuals in each generation 
#define POPULATION_SIZE 100000

// Overloading < operator
bool operator<(individual& ind1, individual& ind2)
{
	return ind1.getFitness() < ind2.getFitness();
}

// Main driver
int main()
{
	srand((unsigned)(time(0)));
	vector<individual> population;

	// Used for getting math functions
	genetic_math mathOp = genetic_math();

	// Inputting target string
	string TARGET;
	cout << "What is your target string?:  ";
	getline(cin, TARGET);

	int compare;
	cout << "Press 0 to compare threaded and unthreaded speeds, press 1 to just run threaded program:  ";
	cin >> compare;

	/*int POPULATION_SIZE;
	cout << "Population size?:  ";
	cin >> POPULATION_SIZE;*/

	// current generation 
	int generation = 0;


	if (compare == 0)
	{
		// Population of individuals
		auto startUnthreaded = high_resolution_clock::now();
		vector<individual> populationUnthreaded = mathOp.create_pop_unthreaded(POPULATION_SIZE, TARGET);
		auto stopUnthreaded = high_resolution_clock::now();
		auto durationUnthreaded = duration_cast<milliseconds>(stopUnthreaded - startUnthreaded);
		cout << durationUnthreaded.count() << " miliseconds to create popluation - unthreaded " << endl;

		auto startThreaded = high_resolution_clock::now();
		population = mathOp.create_pop_threaded(POPULATION_SIZE, TARGET);
		auto stopThreaded = high_resolution_clock::now();
		auto durationThreaded = duration_cast<milliseconds>(stopThreaded - startThreaded);
		cout << durationThreaded.count() << " miliseconds to create popluation - threaded " << endl;
	}
	else if (compare == 1)
	{
		auto startThreaded = high_resolution_clock::now();
		population = mathOp.create_pop_threaded(POPULATION_SIZE, TARGET);
		auto stopThreaded = high_resolution_clock::now();
		auto durationThreaded = duration_cast<milliseconds>(stopThreaded - startThreaded);
		cout << durationThreaded.count() << " miliseconds to create popluation - threaded " << endl;
	}
	else
	{
		cout << "I told you to press 0 or 1";
	}

	bool found = false;













	// Looking for the final string
	while (!found)
	{
		// Sort population by fitness score
		sort(population.begin(), population.end());

		// If the individual having lowest fitness score ie. 0 then we know that we have reached to the target and break the loop 
		if (population[0].getFitness() <= 0)
		{
			found = true;
			break;
		}

		// Otherwise generate new offsprings for new generation 
		vector<individual> new_generation;

		// Perform Elitism, that means 10% of fittest population goes to the next generation 
		int s = (10 * POPULATION_SIZE) / 100;
		for (int i = 0; i < s; i++)
		{
			new_generation.push_back(population[i]);
		}

		// From 50% of fittest population, Individuals will mate to produce offspring 
		s = (90 * POPULATION_SIZE) / 100;
		for (int i = 0; i < s; i++)
		{
			int len = population.size();
			int r = mathOp.random_num(0, 50);
			individual parent1 = population[r];
			r = mathOp.random_num(0, 50);
			individual parent2 = population[r];
			individual offspring = parent1.mate(parent2, TARGET);
			new_generation.push_back(offspring);
		}

		population = new_generation;
		cout << "Generation: " << generation << "\t";
		cout << "String: " << population[0].getChromosome() << "\t";
		cout << "Fitness: " << population[0].getFitness() << "\n";

		generation++;
	}

	cout << "Generation: " << generation << "\t";
	cout << "String: " << population[0].getChromosome() << "\t";
	cout << "Fitness: " << population[0].getFitness() << "\n";
}