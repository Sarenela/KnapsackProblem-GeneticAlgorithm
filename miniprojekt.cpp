
#include <iostream>
#include <string>
#include "GeneticAlgorithm.h"

int main()
{
	try {
		KnapsackProblem problem2("C:\\Users\\user\\Desktop\\test.txt");
		GeneticAlgorithm alg(100, 500, problem2);
		alg.optimize();
	}	
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
