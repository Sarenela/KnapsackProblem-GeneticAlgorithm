#include "Individual.h"
#include "KnapsackProblem.h"

const std::string Individual::ERR_ILLEGAL_ARGUMENT="Failure. The size of the genotype cannot be lesser than 0";

Individual::Individual( int size ) 
{
	if (size < 1) throw Exception(ERR_ILLEGAL_ARGUMENT);
	createGenotype(size);
	fitFlag = 0;
}


Individual::Individual(const KnapsackProblem& problem)  // niemozliwe, zeby problem mial niepoprawne argumenty, wiêc nie trzeba sprawdzac
{
	createGenotype(problem.getDatabase().size());
	updateFitness(problem);
}

Individual:: Individual(const std::vector<bool>& newGen)
{
	genotype = newGen;
	fitFlag = 0;
}

Individual::Individual(const Individual& other)
{
	*this = other;
}



Individual& Individual:: operator=(const Individual& other)
{
	genotype = other.genotype;   
	fitness = other.fitness;
	fitFlag = other.fitFlag;

	return *this;
}

bool Individual::operator<(const Individual& other)
{
	return fitness < other.fitness;
}

bool Individual:: operator>(const Individual& other)
{
	return fitness > other.fitness;
}


Individual::~Individual()
{

}


void  Individual::updateFitness(const KnapsackProblem& problem)
{
	fitness = problem.fitness(genotype);
	fitFlag = 1;
}

double Individual::getFitness() const
{
	return fitness;
}

bool Individual::getFlag()const
{
	return fitFlag;
}

void Individual::mutate(const KnapsackProblem& problem)
{
	Randomizer rand;
	for (int i = 0;i < genotype.size();i++)
	{
		if (rand.randomProb() <= problem.getMutProb()) genotype[i] = !genotype[i];
	}
	updateFitness(problem);
}

void Individual:: printGenotype() const 
{
	for (int i = 0;i < genotype.size();i++)
	{
		std::cout << genotype[i] << " ";
	}
	std::cout << std::endl;
}

void Individual::print() const
{
	std::cout << "osobnik: " << std::endl << "genotyp: ";
	printGenotype();
	std::cout << "fitness: " << fitness << std::endl;
}



std::pair<Individual , Individual> Individual::cross( const Individual& parent, const KnapsackProblem& problem)
{
	Randomizer rand;
	if (rand.randomProb() <= problem.getCrossProb())
	{
		int cutPoint = rand.randomInt(1,genotype.size()-1);
		std::vector<bool> genA;
		std::vector<bool> genB;
		int i = 0;
		while (i < cutPoint)
		{
			genA.push_back(genotype[i]);
			genB.push_back(parent.genotype[i]);
			i++;
		}
		while (i < genotype.size())
		{
			genA.push_back(parent.genotype[i]);
			genB.push_back(genotype[i]);
			i++;
		}
		return std::make_pair(Individual(genA), Individual(genB));  //tworzy nowe elementy, nie maja obliczonego fitnesu, flag =0
	}
	return std::make_pair ( Individual(*this), Individual( parent));  // tworzy nowe  KOPIE starych elementow ,flag =1
}

void Individual::createGenotype(int size)
{
	Randomizer rand;
	for (int i = 0;i < size;i++)
	{
		if (rand.randomProb() > 0.5) genotype.push_back(1);
		else genotype.push_back(0);
	}
}