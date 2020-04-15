#ifndef GENETIC_MATH_H
#define GENETIC_MATH_H

#include <string>
#include <ctime>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class genetic_math
{
private:
	const string GENES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}";
	
public:
	genetic_math();
	int random_num(int start, int end);
	char mutated_genes();
	string create_gnome(string TARGET);
};

#endif