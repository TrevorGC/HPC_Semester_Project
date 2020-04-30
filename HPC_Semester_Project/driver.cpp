#include <iostream>
#include "genetic_math.h"
#include "individual.h"
#include "stdio.h"
#include <chrono> 
using namespace std::chrono;
using namespace std;

// Number of individuals in each generation 
#define POPULATION_SIZE 1000000 //100000


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

	if (compare == 0)
	{
		auto startUnthreaded = high_resolution_clock::now();
		vector<individual> populationUnthreaded = mathOp.create_pop_unthreaded(POPULATION_SIZE, TARGET);
		auto stopUnthreaded = high_resolution_clock::now();
		auto durationUnthreaded = duration_cast<milliseconds>(stopUnthreaded - startUnthreaded);
		cout << endl << durationUnthreaded.count() << " miliseconds to create initial popluation - unthreaded " << endl;

		auto startThreaded = high_resolution_clock::now();
		population = mathOp.create_pop_threaded(POPULATION_SIZE, TARGET);
		auto stopThreaded = high_resolution_clock::now();
		auto durationThreaded = duration_cast<milliseconds>(stopThreaded - startThreaded);
		cout << durationThreaded.count() << " miliseconds to create initial popluation - threaded " << endl << endl;

		auto startUnthreadedTwo = high_resolution_clock::now();
		mathOp.findFinal_unthreaded(population, POPULATION_SIZE, TARGET);
		auto stopUnthreadedTwo = high_resolution_clock::now();
		auto durationUnthreadedTwo = duration_cast<milliseconds>(stopUnthreadedTwo - startUnthreadedTwo);
		cout << durationUnthreadedTwo.count() << " miliseconds to evolve to target string - unthreaded " << endl << endl;

		auto startThreadedTwo = high_resolution_clock::now();
		mathOp.findFinal_threaded(population, POPULATION_SIZE, TARGET);
		auto stopThreadedTwo = high_resolution_clock::now();
		auto durationThreadedTwo = duration_cast<milliseconds>(stopThreadedTwo - startThreadedTwo);
		cout << durationThreadedTwo.count() << " miliseconds to evolve to target string - threaded " << endl << endl;

		cout << "Total time for unthreaded - " << durationUnthreaded.count() + durationUnthreadedTwo.count() << " miliseconds" << endl;
		cout << "Total time for threaded - " << durationThreaded.count() + durationThreadedTwo.count() << " miliseconds" << endl;
		cout << "Threaded improvement over unthreaded - " << (((float) (durationUnthreaded.count() + durationUnthreadedTwo.count()) - (float) (durationThreaded.count() + durationThreadedTwo.count())) / (float) (durationUnthreaded.count() + durationUnthreadedTwo.count())) * 100 << "%" << endl;
	}
	else if (compare == 1)
	{
		auto startThreaded = high_resolution_clock::now();
		population = mathOp.create_pop_threaded(POPULATION_SIZE, TARGET);
		auto stopThreaded = high_resolution_clock::now();
		auto durationThreaded = duration_cast<milliseconds>(stopThreaded - startThreaded);
		cout << endl << durationThreaded.count() << " miliseconds to create popluation - threaded " << endl << endl;

		auto startThreadedTwo = high_resolution_clock::now();
		mathOp.findFinal_threaded(population, POPULATION_SIZE, TARGET);
		auto stopThreadedTwo = high_resolution_clock::now();
		auto durationThreadedTwo = duration_cast<milliseconds>(stopThreadedTwo - startThreadedTwo);
		cout << durationThreadedTwo.count() << " miliseconds to evolve to target string - threaded " << endl;
	}
	else
	{
		vector<int> vecOne{ 1, 2, 3 };
		vector<int> vecTwo{ 4, 5, 6 };
		vector<int> vecThree{ 7, 8, 9 };

		vecOne.insert(vecOne.end(), vecTwo.begin(), vecTwo.end());
		vecOne.insert(vecOne.end(), vecThree.begin(), vecThree.end());

		for (int i = 0; i < vecOne.size(); ++i)
		{
			cout << vecOne.at(i) << ", ";
		}

		cout << "I told you to press 0 or 1";
	}

	
}