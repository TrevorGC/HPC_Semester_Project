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
		void random_num_threaded(int start, int end, int& num);
		char mutated_genes();
		void create_gnome(string TARGET, string& returnGnome);
};

#endif