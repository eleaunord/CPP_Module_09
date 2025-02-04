#include "PmergeMe.hpp"
// 2.5e-05 = 0.000025 seconds (25 microseconds)

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: No input provided.\n";
		return 1;
	}

	try
	{
		// LIST
		printBefore(argv);

		clock_t start = clock(); 

		std::list<std::pair<int, int > > myList;
		int single = -1;
		couplesCreation(&myList, argv, &single); 

		std::list<int> main_chain;
		createMainChain(&main_chain, myList); 

		insertAlgo(myList, &main_chain, single); 

		clock_t end = clock(); 
		printAfter(main_chain);

		std::cout << "Time to process with std::list: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << " s\n";

		// DEQUE
		//printBefore(argv);

		clock_t startDeq = clock(); 

		std::deque<std::pair<int, int > > myDeque;
		int additional_value = -1;
		couplesCreationDeq(&myDeque, argv, &additional_value); 

		std::deque<int> main_chain_deq;
		createMainChainDeq(&main_chain_deq, myDeque); 

		insertAlgo2(myDeque, &main_chain_deq, additional_value);

		clock_t endDeq = clock();

		//printAfterDeq(main_chain_deq);
		std::cout << "Time to process with std::deque: " << static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC << " s\n";
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}

	return 0;
}
