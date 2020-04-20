#ifndef GENETIC_MATH_H
#define GENETIC_MATH_H

#include <string>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>
#include "individual.h"

using namespace std;

class genetic_math
{
private:
	const string GENES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}";

public:
	genetic_math();
	vector<individual> create_pop_unthreaded(int population_size, string TARGET);
	vector<individual> create_pop_threaded(int population_size, string TARGET);
	int random_num(int start, int end);
	char mutated_genes();
	string create_gnome_unthreaded(string TARGET);
	void create_gnome_threaded(string TARGET, string& returnGnome);
};

#endif