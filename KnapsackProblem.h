#ifndef KNAPSACKPROBLEM_H
#define KNAPSACKPROBLEM_H
#include "Individual.h"
#include "FileManager.h"
#include <sstream>
class KnapsackProblem    
{
public:

	static const std::string ERR_ILLEGAL_ARGUMENTS_CONSTRUCTOR;
	static const std::string ERR_ILLEGAL_ARGUMENTS_LOADING_FIRST;
	static const std::string ERR_ILLEGAL_ARGUMENTS_LOADING_REST;

	KnapsackProblem(std::vector<std::pair<double, double>>& dataB, int cap, double crossP, double mutP );
	KnapsackProblem(const std::string& fileName);
	KnapsackProblem(const KnapsackProblem& other);
	KnapsackProblem(KnapsackProblem&& other)=default;
	KnapsackProblem() = delete;

	~KnapsackProblem();
	KnapsackProblem& operator=(const KnapsackProblem& other);
	KnapsackProblem& operator=( KnapsackProblem&& other)=default;

	double fitness(const std::vector<bool>& genotype) const ;
	double getCrossProb() const;
	double getMutProb() const;
	std::vector<std::pair<double, double>> getDatabase() const ;

private:
	std::pair<double, double> entry(const std::string& line);
	bool isPositiveNumber(const std::string& str);

	std::vector<std::pair<double, double>> database;  //first = value,   second = weight
	int capacity;
	double crossProb;
	double mutProb;
};


#endif