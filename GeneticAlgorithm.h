#ifndef GeneticAlgorithm_H
#define GeneticAlgorithm_H
#include "SmartPointer.h"
#include "Individual.h"
#include "Randomizer.h"
#include "KnapsackProblem.h"
class GeneticAlgorithm    
{
public:
	static const std::string ERR_ILLEGAL_ARGUMENTS;

	GeneticAlgorithm(int newIter, int newPopSize,  KnapsackProblem& newProblem);
	GeneticAlgorithm(const GeneticAlgorithm& other);
	GeneticAlgorithm(GeneticAlgorithm&& other)=default;
	GeneticAlgorithm() = delete;

	~GeneticAlgorithm();
	GeneticAlgorithm& operator=(const GeneticAlgorithm& other);
	GeneticAlgorithm& operator=(GeneticAlgorithm&& other)=default;

	int bestParentIndex();  //chooses best parent candidate out of 2 random, returns index
	int bestIndex();        //index of individual in the population

	Individual optimize();
	void clearPop();
	void newPop();
	void initialPop();

private:
	std::vector< Individual > population;  // <single population
	int popSize;
	KnapsackProblem problem;   
	int iterations;
};


#endif