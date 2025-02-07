#include "PmergeMe.hpp"


// Modify the functions to use group_iterator for better group processing
void createMainChain(std::list<int> *main_chain, std::list<std::pair<int, int > > myList) {
    for (auto it = myList.begin(); it != myList.end(); ++it)
        main_chain->push_back(it->second);

    if (!myList.empty())
        main_chain->push_front(myList.begin()->first);
}

void processJacobsthalInsertions(std::list<std::pair<int, int > > &myList, std::list<int> *main_chain) {
    const size_t Jacobsthal[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101};
    int jacobIndex = 1;

    std::list<std::pair<int, int > >::iterator currentCouple;
    std::list<std::pair<int, int > >::iterator lastInsertCouple = myList.begin();

    while (Jacobsthal[jacobIndex] <= myList.size()) {
        currentCouple = myList.begin();
        std::advance(currentCouple, Jacobsthal[jacobIndex] - 1);
        lastInsertCouple = currentCouple;

        int insertCounter = 0;
        while (Jacobsthal[jacobIndex] - insertCounter > Jacobsthal[jacobIndex - 1]) {
            std::list<int>::iterator insertPos = std::find(main_chain->begin(), main_chain->end(), currentCouple->second);
            binarySearchInsertion(main_chain, insertPos, currentCouple->first);
            currentCouple--;
            insertCounter++;
        }
        jacobIndex++;
    }
}

void insertRemainingElements(std::list<std::pair<int, int > > &myList, std::list<int> *main_chain, std::list<std::pair<int, int > >::iterator lastInsertCouple) {
    std::list<std::pair<int, int > >::iterator currentCouple = myList.end();
    if (currentCouple != myList.begin())
        currentCouple--;

    while (currentCouple != lastInsertCouple) {
        std::list<int>::iterator insertPos = std::find(main_chain->begin(), main_chain->end(), currentCouple->second);
        binarySearchInsertion(main_chain, insertPos, currentCouple->first);
        currentCouple--;
    }
}

void binarySearchInsertion(std::list<int> *main_chain, std::list<int>::iterator end, int val)
{
	std::list<int>::iterator place_to_insert = std::lower_bound(main_chain->begin(), end, val);
	main_chain->insert(place_to_insert, val);
}
void insertAlgo(std::list<std::pair<int, int > > myList, std::list<int> *main_chain, int extraValue) {
    processJacobsthalInsertions(myList, main_chain);
    insertRemainingElements(myList, main_chain, myList.begin());

    if (extraValue != -1) {
        binarySearchInsertion(main_chain, main_chain->end(), extraValue);
    }
}

void binarySearchInsertionDeq(std::deque<int> *main_chain, std::deque<int>::iterator end, int val)
{
	std::deque<int>::iterator place_to_insert = std::lower_bound(main_chain->begin(), end, val);
	main_chain->insert(place_to_insert, val);
}

// For deque, similarly
void createMainChainDeq(std::deque<int> *main_chain, std::deque<std::pair<int, int > > myDeque) {
    for (auto it = myDeque.begin(); it != myDeque.end(); ++it)
        main_chain->push_back(it->second);

    if (!myDeque.empty())
        main_chain->push_front(myDeque.begin()->first);
}

void processJacobsthalInsertionsDeq(std::deque<std::pair<int, int > >& myDeque, std::deque<int>* main_chain) {
    const size_t Jacobsthal[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691};
    int jacobIndex = 1;

    std::deque<int>::iterator insertPos;
    std::deque<std::pair<int, int > >::iterator currentCouple;
    std::deque<std::pair<int, int > >::iterator lastInsertCouple = myDeque.begin();

    while (Jacobsthal[jacobIndex] <= myDeque.size()) {
        currentCouple = myDeque.begin() + (Jacobsthal[jacobIndex] - 1);
        lastInsertCouple = currentCouple;

        int insertCounter = 0;
        while (Jacobsthal[jacobIndex] - insertCounter > Jacobsthal[jacobIndex - 1]) {
            insertPos = std::find(main_chain->begin(), main_chain->end(), currentCouple->second);
            binarySearchInsertionDeq(main_chain, insertPos, currentCouple->first);
            currentCouple--;
            insertCounter++;
        }
        jacobIndex++;
    }
}
void insertRemainingElementsDeq(std::deque<std::pair<int, int > > &myDeque, std::deque<int>* main_chain, std::deque<std::pair<int, int > >::iterator lastInsertCouple) {
    (void)myDeque;
    std::list<std::pair<int, int > >::iterator currentCouple = myList.end();
    if (currentCouple != myList.begin())
        currentCouple--;

    while (currentCouple != lastInsertCouple) {
        std::list<int>::iterator insertPos = std::find(main_chain->begin(), main_chain->end(), currentCouple->second);
        binarySearchInsertionDeq(main_chain, insertPos, currentCouple->first);
        currentCouple--;
    }
}
void insertAlgoDeq(std::deque<std::pair<int, int > > myDeque, std::deque<int>* main_chain, int extraValue) {
    processJacobsthalInsertionsDeq(myDeque, main_chain);
    insertRemainingElementsDeq(myDeque, main_chain, myDeque.begin());

    if (extraValue != -1) {
        binarySearchInsertionDeq(main_chain, main_chain->end(), extraValue);
    }
}



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
    return x.second < y.second;
}

// Sort the pairs inside each element of the list or deque
void sortInsideCouple(std::list<std::pair<int, int> > *myList)
{
    for (std::list<std::pair<int, int> >::iterator it = myList->begin(); it != myList->end(); ++it)
    {
        if (it->first > it->second)
            std::swap(it->first, it->second);
    }
}

// Merge sort using group iterators
void mergeSort(std::list<std::pair<int, int> >::iterator start, std::list<std::pair<int, int> >::iterator end)
{
    // Base case: if the list has one or no element, return
    if (std::distance(start, end) <= 1)
        return;

    // Manually calculate the midpoint using advance
    std::list<std::pair<int, int> >::iterator mid = start;
    std::advance(mid, std::distance(start, end) / 2);

    // Recursively divide and sort both halves
    mergeSort(start, mid);
    mergeSort(mid, end);

    // Merge the sorted halves back together
    std::inplace_merge(start, mid, end, compare);
}


// Function to create couples in the list
void couplesCreation(std::list<std::pair<int, int> > *myList, char **argv, int *single)
{
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

    // Sort each couple
    sortInsideCouple(myList);

    // Perform merge sort on the list using group iterators
    mergeSort(myList->begin(), myList->end());
}

// Function to create couples in the deque
void couplesCreationDeq(std::deque<std::pair<int, int> > *myDeque, char **argv, int *additional_value)
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

// Sort the pairs inside the deque
void sortInsideCoupleDeq(std::deque<std::pair<int, int> > *myDeque)
{
    for (std::deque<std::pair<int, int> >::iterator it = myDeque->begin(); it != myDeque->end(); ++it)
    {
        if (it->first > it->second)
            std::swap(it->first, it->second);
    }
}

// Merge sort using group iterators for deque
void mergeSortDeq(std::deque<std::pair<int, int> >::iterator start, std::deque<std::pair<int, int> >::iterator end)
{
    // Base case: if the deque has one or no element, return
    if (std::distance(start, end) <= 1)
        return;

    // Manually calculate the midpoint using advance
    std::deque<std::pair<int, int> >::iterator mid = start;
    std::advance(mid, std::distance(start, end) / 2);

    // Recursively divide and sort both halves
    mergeSortDeq(start, mid);
    mergeSortDeq(mid, end);

    // Merge the sorted halves back together
    std::inplace_merge(start, mid, end, compare);
}
