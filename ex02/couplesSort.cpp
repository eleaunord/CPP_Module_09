#include "PmergeMe.hpp"

/*

MERGE SORT

myList = { (4, 10), (2, 8), (6, 14), (1, 5) } => Each element is a pair (first, second), and sorting is based on .second

1st split :
	Left Half:  {(4, 10), (2, 8)}
	Right Half: {(6, 14), (1, 5)}

2nd split :
	Left Split:
		Left:  {(4, 10)}
		Right: {(2, 8)}
	Right Split:
		Left:  {(6, 14)}
		Right: {(1, 5)}
Each sublist now contains only one element, so recursion stops

Merge
	Merge Left:  {(4, 10)} + {(2, 8)}  →  {(2, 8), (4, 10)}
	Merge Right: {(6, 14)} + {(1, 5)}  →  {(1, 5), (6, 14)}
Final
	{(2, 8), (4, 10)} + {(1, 5), (6, 14)}
	→ Sorted List: {(1, 5), (2, 8), (4, 10), (6, 14)}

*/

// Comparing function for inplace_merge by comparing the second(larger) element of the pairs
bool compare(std::pair<int, int> x, std::pair<int, int> y)
{
	if (x.second < y.second)
		return (1);
	return (0);
}
// Before: {(8,5), (7,3)}
// After: {(5,8), (3,7)}
void sortInsideCouple(std::list<std::pair<int, int > > *myList)
{
	for (std::list<std::pair<int, int > >::iterator it = myList->begin(); it != myList->end(); ++it)
	{
		if (it->first > it->second)
		{
			int temp = it->first;
			it->first = it->second;
			it->second = temp;
		}
	}
}

// Do merge sort with recursive approach splitting the list in half each time and merging them back together
void mergeSort(std::list<std::pair<int, int > >::iterator start, std::list<std::pair<int, int > >::iterator end, size_t size)
{
	// case when it's already sorted
	if (size == 0 && start != end)
		size = std::distance(start, end);
	if (size <= 1)
		return;

	size_t firstHalf = size / 2;
	size_t secondHalf = size - firstHalf;
	std::list<std::pair<int, int > >::iterator center = start;
	// Move the iterator to the center of the list
	std::advance(center, firstHalf);

	mergeSort(start, center, firstHalf); // start to center
	mergeSort(center, end, secondHalf);	 // center to end

	std::inplace_merge(start, center, end, &compare); // merges the two sorted halves back together
													  // we need a comparaison function that orders elements based on their second values
}

void couplesCreation(std::list<std::pair<int, int > > *myList, char **argv, int *single)
{
	// std::pair<int, int> == template that holds 2 values of the specified types
	int i = 1;

	while (argv[i])
	{
		if (argv[i] && argv[i + 1])
		{
			std::pair<int, int> myCouple(std::atoi(argv[i]), std::atoi(argv[i + 1]));
			myList->push_back(myCouple);
			i += 2;
		}
		else
		{
			*single = std::atoi(argv[i]);
			i++;
		}
	}
	sortInsideCouple(myList);
	mergeSort(myList->begin(), myList->end(), 0);
}

/* Deque functions */

void couplesCreationDeq(std::deque<std::pair<int, int > > *myDeque, char **argv, int *additional_value)
{
	int i = 1;

	while (argv[i])
	{
		if (argv[i] && argv[i + 1])
		{
			std::pair<int, int> pair_temp(std::atoi(argv[i]), std::atoi(argv[i + 1]));
			myDeque->push_back(pair_temp);
			i += 2;
		}
		else
		{
			*additional_value = std::atoi(argv[i]);
			i++;
		}
	}
}

void sortInsideCoupleDeq(std::deque<std::pair<int, int > > *myDeque)
{
	for (std::deque<std::pair<int, int > >::iterator it = myDeque->begin(); it != myDeque->end(); ++it)
	{
		if (it->first > it->second)
		{
			int temp = it->first;
			it->first = it->second;
			it->second = temp;
		}
	}
}

void mergeSortDeq(std::deque<std::pair<int, int > >::iterator start, std::deque<std::pair<int, int > >::iterator end, size_t size)
{
	if (size == 0 && start != end)
		size = std::distance(start, end);
	if (size <= 1)
		return;

	size_t firstHalf = size / 2;
	size_t secondHalf = size - firstHalf;
	std::deque<std::pair<int, int > >::iterator center = start + firstHalf;

	mergeSortDeq(start, center, firstHalf);
	mergeSortDeq(center, end, secondHalf);
	std::inplace_merge(start, center, end, &compare);
}