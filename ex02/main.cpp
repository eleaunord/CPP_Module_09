#include "PmergeMe.hpp"
#include <iostream>
#include <ctime>
#include <list>
#include <deque>

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: No input provided.\n";
		return 1;
	}

	try
	{
		
		int numElements = argc - 1;  

		// LIST
		//printBefore(argv);

		clock_t start = clock(); 

		std::list<std::pair<int, int > > myList;
		int single = -1;
		couplesCreation(&myList, argv, &single); 

		std::list<int> main_chain;
		createMainChain(&main_chain, myList); 

		insertAlgo(myList, &main_chain, single); 

		clock_t end = clock(); 
		//std::cout << std::endl;
		//printAfter(main_chain);

		double elapsedList = (static_cast<double>(end - start) * 1000000.0) / CLOCKS_PER_SEC;
		std::cout << "Time to process a range of " << numElements << " elements with std::list: " << elapsedList << " us\n";

		// DEQUE
		//std::cout << std::endl;
		printBefore(argv);
		clock_t startDeq = clock(); 

		std::deque<std::pair<int, int > > myDeque;
		int additional_value = -1;
		couplesCreationDeq(&myDeque, argv, &additional_value); 

		std::deque<int> main_chain_deq;
		createMainChainDeq(&main_chain_deq, myDeque); 

		insertAlgoDeq(myDeque, &main_chain_deq, additional_value);

		clock_t endDeq = clock();
		//std::cout << std::endl;
		printAfterDeq(main_chain_deq);

		double elapsedDeque = (static_cast<double>(endDeq - startDeq) * 1000000.0) / CLOCKS_PER_SEC;
		std::cout << "Time to process a range of " << numElements << " elements with std::deque: " << elapsedDeque << " us\n";
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}

	return 0;
}
