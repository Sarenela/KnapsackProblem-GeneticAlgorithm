#ifndef Randomizer_H
#define Randomizer_H
#include <iostream>
#include <random>
class Randomizer
{
public:
	Randomizer();
	int randomInt(int low, int high);
	double randomProb();

private:
	std::mt19937 gen;
};
#endif
