#include "GeneticAlgorithm.h"


const std::string GeneticAlgorithm::ERR_ILLEGAL_ARGUMENTS="Failure while creating the GeneticAlgorithm. The arguments are wrong - make sure the number of iterations is greater than 1, and the population size greater than 2";

GeneticAlgorithm::GeneticAlgorithm(int newIter, int newPopSize,  KnapsackProblem newProblem) :problem(newProblem)
{
	if (newIter < 1 || newPopSize < 2) throw Exception(ERR_ILLEGAL_ARGUMENTS);

	iterations = newIter;
	popSize = newPopSize;
	initialPop();
}

GeneticAlgorithm::GeneticAlgorithm(const GeneticAlgorithm& other):problem(other.problem)
{
	iterations = other.iterations;
	popSize = other.popSize;
	population = other.population;
}


GeneticAlgorithm::~GeneticAlgorithm()
{

}

GeneticAlgorithm& GeneticAlgorithm::operator=(const GeneticAlgorithm& other)
{
	iterations = other.iterations;
	popSize = other.popSize;
	population = other.population;      
	problem = other.problem;

	return *this;
}




Individual GeneticAlgorithm::optimize()  //GLOWNA METODA PROGRAMU
{
	Individual bestInd = population[bestIndex()];

	for (int i = 0;i < iterations;i++)
	{
		newPop();
		Individual currBestInd = population[bestIndex()];

		if (currBestInd > bestInd)	bestInd = currBestInd;                             
	}

	std::cout << "najlepszy ";
	bestInd.print();

	return bestInd;
}

void GeneticAlgorithm::newPop()  //popSize moze siê zmienic o 1, jezeli poczatkowy popSIze jest nieparzysty - nie uwazam tego za problem
{
	std::vector< Individual> newGen;

	for (int i = 0;i < popSize;i += 2)
	{
		auto children = population[bestParentIndex()].cross(population[bestParentIndex()], problem);

		(children.first).mutate(problem);
		(children.second).mutate(problem);

		if (!(children.first).getFlag()) (children.first).updateFitness(problem);   
		if (!(children.second).getFlag()) (children.second).updateFitness(problem);

		newGen.push_back(children.first);
		newGen.push_back(children.second);
	}
	clearPop();
	population = newGen;
	popSize = population.size();
}

void GeneticAlgorithm::initialPop()
{
	for (int i = 0;i < popSize;i++)
	{
		population.push_back(Individual(problem));   //flag =1 
	}
}

void GeneticAlgorithm::clearPop()
{
	population.clear();   
}




int GeneticAlgorithm::bestParentIndex()
{
	Randomizer rand;
	int first =rand.randomInt(0, popSize-1);
	int second = rand.randomInt(0, popSize-1);
	return   population[first] > population[second] ? first : second;
}

int GeneticAlgorithm::bestIndex()    //TRZEBA ZNALEZC NAJLEPSZEGO ZE WSZYSTKICH ITERACJI
{
	int best=0;
	for (int i = 0; i < popSize;i++)
	{
		if (!population[i].getFlag()) population[i].updateFitness(problem);
		if (population[best] < population[i]) best = i;
	}
	return best;

}

