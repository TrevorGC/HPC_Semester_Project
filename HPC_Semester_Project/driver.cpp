#include <iostream>
#include "genetic_math.h"
#include "individual.h"
#include <thread>
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

	// Used for getting math functions
	genetic_math mathOp = genetic_math();

	// Inputting target string
	string TARGET;
	cout << "What is your target string?:  ";
	getline(cin, TARGET);

	// current generation 
	int generation = 0;

	// Population of individuals
	vector<individual> population;
	bool found = false;




	/*
	PARRALIZE
	THIS 
	FUNCTION
	*/
	int remainingPop = POPULATION_SIZE;
	while (true)
	{
		string gnomeOne, gnomeTwo, gnomeThree, gnomeFour, gnomeFive, gnomeSix, gnomeSeven, gnomeEight, gnomeNine, gnomeTen;

		thread threadOne(&genetic_math::create_gnome, mathOp, TARGET, std::ref(gnomeOne));
		thread threadTwo(&genetic_math::create_gnome, mathOp, TARGET, std::ref(gnomeTwo));
		thread threadThree(&genetic_math::create_gnome, mathOp, TARGET, std::ref(gnomeThree));
		thread threadFour(&genetic_math::create_gnome, mathOp, TARGET, std::ref(gnomeFour));
		thread threadFive(&genetic_math::create_gnome, mathOp, TARGET, std::ref(gnomeFive));
		thread threadSix(&genetic_math::create_gnome, mathOp, TARGET, std::ref(gnomeSix));
		thread threadSeven(&genetic_math::create_gnome, mathOp, TARGET, std::ref(gnomeSeven));
		thread threadEight(&genetic_math::create_gnome, mathOp, TARGET, std::ref(gnomeEight));
		thread threadNine(&genetic_math::create_gnome, mathOp, TARGET, std::ref(gnomeNine));
		thread threadTen(&genetic_math::create_gnome, mathOp, TARGET, std::ref(gnomeTen));

		threadOne.join();
		threadTwo.join();
		threadThree.join();
		threadFour.join();
		threadFive.join();
		threadSix.join();
		threadSeven.join();
		threadEight.join();
		threadNine.join();
		threadTen.join();

		individual individualOne(gnomeOne, TARGET), individualTwo(gnomeTwo, TARGET), individualThree(gnomeThree, TARGET), individualFour(gnomeFour, TARGET), individualFive(gnomeFive, TARGET), individualSix(gnomeSix, TARGET), individualSeven(gnomeSeven, TARGET), individualEight(gnomeEight, TARGET), individualNine(gnomeNine, TARGET), individualTen(gnomeTen, TARGET);

		population.push_back(individualOne);
		population.push_back(individualTwo);
		population.push_back(individualThree);
		population.push_back(individualFour);
		population.push_back(individualFive);
		population.push_back(individualSix);
		population.push_back(individualSeven);
		population.push_back(individualEight);
		population.push_back(individualNine);
		population.push_back(individualTen);

		if (remainingPop == 10)
		{
			break;
		}
		else
		{
			remainingPop = remainingPop - 10;
		}
	}

	// create initial population 
	/*for (int i = 0; i < POPULATION_SIZE; i++)
	{
		string gnome = mathOp.create_gnome(TARGET);
		population.push_back(individual(gnome, TARGET));
	}*/
	
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




		/*
		PARRALIZE
		THIS
		FUNCTION
		*/
		// Perform Elitism, that means 10% of fittest population goes to the next generation 
		int s = (10 * POPULATION_SIZE) / 100;
		for (int i = 0; i < s; i++)
		{
			new_generation.push_back(population[i]);
		}





		/*
		PARRALIZE
		THIS
		FUNCTION
		*/
		// From 50% of fittest population, Individuals will mate to produce offspring 
		s = (90 * POPULATION_SIZE) / 100;

		while (true)
		{
			int len = population.size();
			int r1, r2, r3, r4, r5, r6, r7, r8, r9, r10;

			thread threadOne(&genetic_math::random_num_threaded, mathOp, 0, 50, std::ref(r1));
			thread threadTwo(&genetic_math::random_num_threaded, mathOp, 0, 50, std::ref(r2));
			thread threadThree(&genetic_math::random_num_threaded, mathOp, 0, 50, std::ref(r3));
			thread threadFour(&genetic_math::random_num_threaded, mathOp, 0, 50, std::ref(r4));
			thread threadFive(&genetic_math::random_num_threaded, mathOp, 0, 50, std::ref(r5));
			thread threadSix(&genetic_math::random_num_threaded, mathOp, 0, 50, std::ref(r6));
			thread threadSeven(&genetic_math::random_num_threaded, mathOp, 0, 50, std::ref(r7));
			thread threadEight(&genetic_math::random_num_threaded, mathOp, 0, 50, std::ref(r8));
			thread threadNine(&genetic_math::random_num_threaded, mathOp, 0, 50, std::ref(r9));
			thread threadTen(&genetic_math::random_num_threaded, mathOp, 0, 50, std::ref(r10));

			threadOne.join();
			threadTwo.join();
			threadThree.join();
			threadFour.join();
			threadFive.join();
			threadSix.join();
			threadSeven.join();
			threadEight.join();
			threadNine.join();
			threadTen.join();

			individual parent1 = population[r1], parent2 = population[r2], parent3 = population[r3], parent4 = population[r4], parent5 = population[r5], parent6 = population[r6], parent7 = population[r7], parent8 = population[r8], parent9 = population[r9], parent10 = population[r10];

			individual offspringOne, offspringTwo, offspringThree, offspringFour, offspringFive;

			thread threadEleven(&individual::mate, parent1, parent2, TARGET, std::ref(offspringOne));
			thread threadTwelve(&individual::mate, parent3, parent4, TARGET, std::ref(offspringTwo));
			thread threadThirteen(&individual::mate, parent5, parent6, TARGET, std::ref(offspringThree));
			thread threadFourteen(&individual::mate, parent7, parent8, TARGET, std::ref(offspringFour));
			thread threadFifteen(&individual::mate, parent9, parent10, TARGET, std::ref(offspringFive));

			threadEleven.join();
			threadTwelve.join();
			threadThirteen.join();
			threadFourteen.join();
			threadFifteen.join();

			new_generation.push_back(offspringOne);
			new_generation.push_back(offspringTwo);
			new_generation.push_back(offspringThree);
			new_generation.push_back(offspringFour);
			new_generation.push_back(offspringFive);

			if (s == 10)
			{
				break;
			}
			else
			{
				s = s - 10;
			}
		}

		/*for (int i = 0; i < s; i++)
		{
			int len = population.size();
			int r = mathOp.random_num(0, 50);
			individual parent1 = population[r];
			r = mathOp.random_num(0, 50);
			individual parent2 = population[r];
			individual offspring = parent1.mate(parent2, TARGET);
			new_generation.push_back(offspring);
		}*/

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