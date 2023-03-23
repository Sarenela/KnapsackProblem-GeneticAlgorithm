#include "KnapsackProblem.h"

const std::string KnapsackProblem::ERR_ILLEGAL_ARGUMENTS_CONSTRUCTOR = "Failure while creating the KnapsackProblem. The arguments are wrong - make sure that capacity and database size are grater than 1 and that probabilities of mutation and crossing are between 0 and 1.";
const std::string KnapsackProblem::ERR_ILLEGAL_ARGUMENTS_LOADING_FIRST = "Failure while creating the KnapsackProblem. The file has a wrong format - make sure that the first line has 3 values: capacity greater than 0 and 2 probabilities between 0 and 1 . everithing separated by spaces";
const std::string KnapsackProblem::ERR_ILLEGAL_ARGUMENTS_LOADING_REST = "Failure while creating the KnapsackProblem. The file has a wrong format - make sure that the lines have 2 positive values separated by spaces. ";


KnapsackProblem::KnapsackProblem(const KnapsackProblem& other)
{
	(*this) = other;

}

KnapsackProblem::KnapsackProblem(std::vector<std::pair<double, double>>& dataB, int cap, double crossP, double mutP)
{
	if (crossP > 1 || crossP < 0 || mutP>1 || mutP < 0 || cap <=0 || dataB.size() < 1) throw Exception(ERR_ILLEGAL_ARGUMENTS_CONSTRUCTOR);

	database = dataB;
	capacity = cap;
	crossProb = crossP;
	mutProb = mutP;

}

KnapsackProblem::KnapsackProblem(const std::string& fileName)     // forma  pliku > pierwsza linia : [capacity] [crossProb] [mutProb], nastepne: [value] [ weight]
{
	FileManager fileM(fileName);//can throw, custom
	std::vector<std::string> data;

	data = fileM.load();  //can throw, custom
	fileM.close();        //can throw, custom 
	std::string valid, valid2, valid3;
	try
	{
		std::stringstream ss(data[0]);
		ss >> valid >> valid2 >> valid3;
	}
	catch (...)
	{
		throw Exception(ERR_ILLEGAL_ARGUMENTS_LOADING_FIRST);
	}

	if (isPositiveNumber(valid) && isPositiveNumber(valid2) && isPositiveNumber(valid3))
	{
		capacity = std::stod(valid);
		crossProb = std::stod(valid2);
		mutProb = std::stod(valid3);
	}
	else throw Exception(ERR_ILLEGAL_ARGUMENTS_LOADING_FIRST);

	if (crossProb<0 || crossProb>1  || mutProb >1 || mutProb<0)  	throw Exception(ERR_ILLEGAL_ARGUMENTS_LOADING_FIRST);
	
	data.erase(data.begin());
	for (std::string line : data)  database.push_back(entry(line));   //can throw, custom
}



KnapsackProblem ::~KnapsackProblem()
{

}

KnapsackProblem& KnapsackProblem ::operator=(const KnapsackProblem& other)
{
	database = other.database;
	capacity = other.capacity;
	crossProb = other.crossProb;
	mutProb = other.mutProb;
	return *this;
}

double KnapsackProblem::getCrossProb()const 
{
	return crossProb;
}
double KnapsackProblem::getMutProb() const
{
	return mutProb;
}

std::vector<std::pair<double, double>> KnapsackProblem::getDatabase() const
{
	return database;
}


double KnapsackProblem::fitness(const std::vector<bool>& genotype) const
{
	double weightSum = 0;
	double valueSum = 0;

	for (int i = 0; i < genotype.size(); i++)
	{
		if (genotype[i])
		{
			valueSum += database[i].first;
			weightSum += database[i].second;
		}
	}
	if (weightSum <= capacity) return valueSum;
	return 0;
}


std::pair<double, double> KnapsackProblem:: entry(const std::string& line)
{
	std::stringstream ss(line);
	std::string valid, valid2;

	ss >> valid >> valid2;      

	if (!isPositiveNumber(valid) || !isPositiveNumber(valid2)) throw Exception(ERR_ILLEGAL_ARGUMENTS_LOADING_REST);
	return std::make_pair(std::stod(valid),std::stod(valid2));
}


bool KnapsackProblem:: isPositiveNumber(const std::string& str)  // nie akceptuje ujemnych hehe , tylko liczbt, dopuszczalna 1 Kropka, first char to number, ostatnia tez
{
	int numOfPeriods=0;
	if (str[0] < 48 || str[0] > 57) return false;  //if true then for sure 1 number

	for (int i=1;i<str.size()-1;i++)
	{
		if (str[i] == 46) numOfPeriods++;
		else if (str[i] < 48 || str[i] > 57) return false;

		if (numOfPeriods > 1) return false;
	}

	return (str[str.size()-1]>= 48 && str[str.size() - 1]<=57);

}