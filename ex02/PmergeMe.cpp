#include "PmergeMe.hpp"

//LIST

void createMainChain(std::list<int> *main_chain, std::list<std::pair<int, int > > myList)
{
	for (std::list<std::pair<int, int > >::iterator it = myList.begin(); it != myList.end(); ++it)
		main_chain->push_back(it->second);

	// the first number of pend can always be inserted as the first number in the main chain.
	// it's always smaller than it's paired number
	if (!myList.empty())
		main_chain->push_front(myList.begin()->first);
}
/*
Extracts the larger number of each pair into main_chain
First element of min list is inserted at the front

Pairs: {(3,7), (5,8)}
Main Chain: [3, 7, 8]
*/

// Do a binary search to find the correct position within the slice of the main chain and insert the value
void binarySearchInsertion(std::list<int> *main_chain, std::list<int>::iterator end, int val)
{
	std::list<int>::iterator place_to_insert = std::lower_bound(main_chain->begin(), end, val);
	main_chain->insert(place_to_insert, val);
}

/*
Uses std::lower_bound() to find the correct position
Efficiently inserts elements while keeping main_chain sorted
Main Chain: [3, 7, 8]
Insert 5 → [3, 5, 7, 8]
*/

void insertAlgo(std::list<std::pair<int, int > > myList, std::list<int> *main_chain, int extraValue)
{
	const size_t Jacobsthal[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};
	int jacobIndex = 1;

	std::list<int>::iterator insertPos; // find inseration point in main chain
	std::list<std::pair<int, int > >::iterator currentCouple; // traverse the list of pairs
	std::list<std::pair<int, int > >::iterator lastInsertCouple = myList.begin(); // sortes the last Jacobsthal-inserted element.

	while (Jacobsthal[jacobIndex] <= myList.size())
	{
		currentCouple = myList.begin();
		std::advance(currentCouple, Jacobsthal[jacobIndex] - 1); // Moves currentCouple to the Jacobsthal[jacobIndex] - 1 position.
		lastInsertCouple = currentCouple;			 // Updates lastInsertCouple to track the last Jacobsthal-inserted element.

		int insertCounter = 0;
		while (Jacobsthal[jacobIndex] - insertCounter > Jacobsthal[jacobIndex - 1])
		{
			insertPos = std::find(main_chain->begin(), main_chain->end(), currentCouple->second);
			binarySearchInsertion(main_chain, insertPos, currentCouple->first);
			currentCouple--;
			insertCounter++;
		}
		jacobIndex++;
	}

	// if the Jacobsthal number is larger than the size of the list, insert the remaining elements
	if (Jacobsthal[jacobIndex] != myList.size())
	{
		currentCouple = myList.end();
		if (currentCouple != myList.begin())
			currentCouple--;
		while (currentCouple != lastInsertCouple)
		{
			insertPos = std::find(main_chain->begin(), main_chain->end(), currentCouple->second);
			binarySearchInsertion(main_chain, insertPos, currentCouple->first);
			currentCouple--;
		}
	}

	if (extraValue != -1)
	{
		binarySearchInsertion(main_chain, main_chain->end(), extraValue);
	}
}

/*
  Jacobsthal sequence : Jn​=Jn−1​+2Jn−2
  determine insertion order
*/

// DEQUE

void createMainChainDeq(std::deque<int> *main_chain, std::deque<std::pair<int, int > > myDeque)
{
	for (std::deque<std::pair<int, int > >::iterator it = myDeque.begin(); it != myDeque.end(); ++it)
		main_chain->push_back(it->second);
	if (!myDeque.empty())
		main_chain->push_front(myDeque.begin()->first);
}

void binarySearchInsertionDeq(std::deque<int> *main_chain, std::deque<int>::iterator end, int val)
{
	std::deque<int>::iterator place_to_insert = std::lower_bound(main_chain->begin(), end, val);
	main_chain->insert(place_to_insert, val);
}

void insertAlgo2(std::deque<std::pair<int, int > > myDeque, std::deque<int> *main_chain, int extraValue)
{
	const size_t Jacobsthal[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};
	int jacobIndex = 1;

	std::deque<int>::iterator insertPos;
	std::deque<std::pair<int, int > >::iterator currentCouple;
	std::deque<std::pair<int, int > >::iterator lastInsertCouple = myDeque.begin();

	while (Jacobsthal[jacobIndex] <= myDeque.size())
	{
		currentCouple = myDeque.begin() + (Jacobsthal[jacobIndex] - 1);
		lastInsertCouple = currentCouple;

		int insertCounter = 0;
		while (Jacobsthal[jacobIndex] - insertCounter > Jacobsthal[jacobIndex - 1])
		{
			insertPos = std::find(main_chain->begin(), main_chain->end(), currentCouple->second);
			binarySearchInsertionDeq(main_chain, insertPos, currentCouple->first);
			currentCouple--;
			insertCounter++;
		}
		jacobIndex++;
	}

	if (Jacobsthal[jacobIndex] != myDeque.size())
	{
		currentCouple = myDeque.end();
		if (currentCouple != myDeque.begin())
			currentCouple--;
		while (currentCouple != lastInsertCouple)
		{
			insertPos = std::find(main_chain->begin(), main_chain->end(), currentCouple->second);
			binarySearchInsertionDeq(main_chain, insertPos, currentCouple->first);
			currentCouple--;
		}
	}

	if (extraValue != -1)
	{
		binarySearchInsertionDeq(main_chain, main_chain->end(), extraValue);
	}
}
