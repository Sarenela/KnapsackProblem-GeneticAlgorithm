#ifndef INDIVIDUAL_H 
//przekazujemy referencje do problemu, ktoru zawiera genotyp, osobnik przekazuje problemowi genotyp, problem oblicza fitness, fitness mozna zapisac w polu, dodac flage
// evaluate - wywoluje funkcje evaluate z klasy problemu,  -> double(moze byc void) evaluate(const Problem& problem){problem.evaluate(genotype);} ; lub {return fitness}(jezeli osobnik ma pole fintess
// osobnicy ukryty w alg gen, alg gen tworzy swoje osobniki
//
#define INDIVIDUAL_H
#include <vector>
#include <utility>
#include "SmartPointer.h"
#include "Randomizer.h"


class KnapsackProblem;     ///forward declaration, tells the compiler that a class exists

class Individual
{
public:

	static const std::string ERR_ILLEGAL_ARGUMENT;

	Individual( int size );
	Individual(const KnapsackProblem& problem);   //widzi knapsack problem jakos int?? przeciez jest include
	Individual(const std::vector<bool>&  newGen);
	Individual(const Individual& other);
	Individual(Individual&& other)=default;
	Individual()=delete;


	Individual& operator=(const Individual& other);
	Individual& operator=(Individual&& other)=default;
	bool operator<(const Individual& other);
	bool operator>(const Individual& other);


	~Individual();
	void createGenotype(int size);
	void updateFitness(const KnapsackProblem& problem);
	double getFitness()const;
	bool getFlag()const;
	void printGenotype() const;
	void print() const;
	void mutate(const KnapsackProblem& problem);
	std::pair<Individual ,Individual> cross(const Individual& parent, const KnapsackProblem& problem);

private:

	std::vector<bool> genotype;   //indeksy bazy danych danych ktore zawiera plecak 
	double fitness;
	bool fitFlag;            // flaga czy fitness obliczone
};
#endif

