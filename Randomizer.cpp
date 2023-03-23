#include "Randomizer.h"

Randomizer::Randomizer() : gen(std::random_device()()){}

int Randomizer::randomInt(int low, int high)
{
    std::uniform_int_distribution<> distrib(low, high);
    return distrib(gen);
}

double Randomizer::randomProb()
{
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(gen);
}