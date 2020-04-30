#include "genetic_math.h"
#include "individual.h"
#include <thread>
#include <vector>
#include <iostream>

// Overloading < operator
bool operator<(individual& ind1, individual& ind2)
{
	return ind1.getFitness() < ind2.getFitness();
}

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
	for (int i = 0; i < len; i++)
	{
		returnGnome += mutated_genes();
	}
}


void genetic_math::findFinal_threaded(vector <individual> population, int POPULATION_SIZE, string TARGET)
{
	bool found = false;
	genetic_math mathOp = genetic_math();
	individual indivOp = individual();

	// current generation 
	int generation = 0;

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

		vector<individual> new_generation_first;
		vector<individual> new_generation_second;

		thread threadOne(&individual::next_Generation, indivOp, 0, s / 2, population, TARGET, std::ref(new_generation_first));
		thread threadTwo(&individual::next_Generation, indivOp, s / 2, s, population, TARGET, std::ref(new_generation_second));

		threadOne.join();
		threadTwo.join();

		new_generation.insert(new_generation.end(), new_generation_first.begin(), new_generation_first.end());
		new_generation.insert(new_generation.end(), new_generation_second.begin(), new_generation_second.end());

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

void individual::next_Generation(int start, int end, vector<individual> population, string TARGET, vector<individual>& newGeneration)
{
	genetic_math mathOp = genetic_math();

	for (int i = start; i < end; i++)
	{
		int r = mathOp.random_num(0, 50);
		individual parent1 = population[r];
		r = mathOp.random_num(0, 50);
		individual parent2 = population[r];
		individual offspring = parent1.mate(parent2, TARGET);
		newGeneration.push_back(offspring);
	}
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

void genetic_math::findFinal_unthreaded(vector<individual> population, int POPULATION_SIZE, string TARGET)
{
	bool found = false;
	genetic_math mathOp = genetic_math();

	// current generation 
	int generation = 0;

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
			//int len = population.size();
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

// Function to generate random numbers in given range.  This is used to select a random character from the gene pool
float genetic_math::random_num(int start, int end)
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
individual::individual()
{
	return;
}

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