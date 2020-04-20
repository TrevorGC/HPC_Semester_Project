#include "genetic_math.h"
#include "individual.h"
#include <thread>
#include <vector>
#include <iostream>

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Math constructor
genetic_math::genetic_math()
{
	return;
}











// Create initial popluation - threaded
vector<individual> genetic_math::create_pop_threaded(int population_size, string TARGET)
{
	vector<individual> population;
	genetic_math mathOp = genetic_math();

	string gnomeOne, gnomeTwo;

	thread threadOne(&genetic_math::create_gnome_threaded, mathOp, TARGET, std::ref(gnomeOne));
	thread threadTwo(&genetic_math::create_gnome_threaded, mathOp, TARGET, std::ref(gnomeTwo));


	threadOne.join();
	threadTwo.join();


	while (true)
	{
		individual individualOne(gnomeOne, TARGET), individualTwo(gnomeTwo, TARGET);

		population.push_back(individualOne);
		population.push_back(individualTwo);


		if (population_size == 2)
		{
			break;
		}
		else
		{
			population_size = population_size - 2;
		}
	}

	return population;
}

// Create chromosome or string of genes.  Creating a gnome from mutated genes. - threaded ver
void genetic_math::create_gnome_threaded(string TARGET, string& returnGnome)
{
	int len = TARGET.size();
	string gnome = "";
	for (int i = 0; i < len; i++)
		gnome += mutated_genes();
	returnGnome = gnome;
}



// Create initial popluation - unthreaded
vector<individual> genetic_math::create_pop_unthreaded(int population_size, string TARGET)
{
	vector<individual> population;
	genetic_math mathOp = genetic_math();

	for (int i = 0; i < population_size; i++)
	{
		string gnome = mathOp.create_gnome_unthreaded(TARGET);
		population.push_back(individual(gnome, TARGET));
	}

	return population;
}

// Create chromosome or string of genes.  Creating a gnome from mutated genes. - unthreaded ver
string genetic_math::create_gnome_unthreaded(string TARGET)
{
	int len = TARGET.size();
	string gnome = "";
	for (int i = 0; i < len; i++)
		gnome += mutated_genes();
	return gnome;
}











// Function to generate random numbers in given range.  This is used to select a random character from the gene pool
int genetic_math::random_num(int start, int end)
{
	int range = (end - start) + 1;
	int random_int = start + (rand() % range);
	return random_int;
}

// Create random genes for mutation.  Using hte random numbers to select a gene from the gene pool and add it to the current gnome.
char genetic_math::mutated_genes()
{
	int len = GENES.size();
	int r = random_num(0, len - 1);
	return GENES[r];
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Individual constructor
individual::individual(string chromosome, string TARGET)
{
	this->chromosome = chromosome;
	fitness = cal_fitness(TARGET);
}

// Perform mating and produce new offspring 
individual individual::mate(individual parent2, string TARGET)
{
	// Used for getting math functions
	genetic_math mathOp = genetic_math();

	// chromosome for offspring 
	string child_chromosome = "";

	int len = chromosome.size();
	for (int i = 0; i < len; i++)
	{
		// random probability 
		float p = mathOp.random_num(0, 100) / 100;

		// if prob is less than 0.45, insert gene from parent 1 
		if (p < 0.45)
		{
			child_chromosome += chromosome[i];
		}

		// if prob is between 0.45 and 0.90, insert gene from parent 2 
		else if (p < 0.90)
		{
			child_chromosome += parent2.chromosome[i];
		}

		// otherwise insert random gene(mutate), for maintaining diversity 
		else
		{
			child_chromosome += mathOp.mutated_genes();
		}
	}

	// create new Individual(offspring) using generated chromosome for offspring 
	return individual(child_chromosome, TARGET);
}

// Calculate fittness score, it is the number of characters in string which differ from target string.
int individual::cal_fitness(string TARGET)
{
	int len = TARGET.size();
	int fitness = 0;
	for (int i = 0; i < len; i++)
	{
		if (chromosome[i] != TARGET[i])
			fitness++;
	}
	return fitness;
}

// Return individual's chromosome
string individual::getChromosome()
{
	return chromosome;
}

// Return individual's fitness
int individual::getFitness()
{
	return fitness;
}