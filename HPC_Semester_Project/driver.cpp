#include <iostream>
#include "genetic_math.h"
#include "individual.h"
using namespace std;

// Number of individuals in each generation 
#define POPULATION_SIZE 100

// Overloading < operator 
bool operator<(individual& ind1, individual& ind2)
{
	return ind1.getFitness() < ind2.getFitness();
}


int main()
{
	// Target string to be generated 
	string TARGET;
	cout << "What is your target string?:  ";
	cin >> TARGET;

	srand((unsigned)(time(0)));

	// math operator
	genetic_math mathOp = genetic_math();

	// current generation 
	int generation = 0;

	vector<individual> population;
	bool found = false;

	// create initial population 
	for (int i = 0; i < POPULATION_SIZE; i++)
	{
		string gnome = mathOp.create_gnome(TARGET);
		population.push_back(individual(gnome, TARGET));
	}

	while (!found)
	{
		// sort the population in increasing order of fitness score 
		sort(population.begin(), population.end());

		// if the individual having lowest fitness score ie. 
		// 0 then we know that we have reached to the target 
		// and break the loop 
		if (population[0].getFitness() <= 0)
		{
			found = true;
			break;
		}

		// Otherwise generate new offsprings for new generation 
		vector<individual> new_generation;

		// Perform Elitism, that mean 10% of fittest population 
		// goes to the next generation 
		int s = (10 * POPULATION_SIZE) / 100;
		for (int i = 0; i < s; i++)
			new_generation.push_back(population[i]);

		// From 50% of fittest population, Individuals 
		// will mate to produce offspring 
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