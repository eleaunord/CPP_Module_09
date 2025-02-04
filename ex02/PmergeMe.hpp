#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <ctime>


class PmergException : public std::runtime_error
{
	public:
		explicit PmergException(std::string msg) : runtime_error(msg) {}
};

// LIST
void createMainChain(std::list<int> *main_chain, std::list<std::pair<int, int > > myList);
void binarySearchInsertion(std::list<int> *main_chain, std::list<int>::iterator end, int val);
void insertAlgo(std::list<std::pair<int, int > > myList, std::list<int> *main_chain, int extraValue);
void sortInsideCouple(std::list<std::pair<int, int > > *myList);
void mergeSort(std::list<std::pair<int, int > >::iterator start, std::list<std::pair<int, int > >::iterator end, size_t size);
void couplesCreation(std::list<std::pair<int, int > > *myList, char **argv, int *single);


// DEQUE
void createMainChainDeq(std::deque<int> *main_chain, std::deque<std::pair<int, int > > myDeque);
void binarySearchInsertionDeq(std::deque<int> *main_chain, std::deque<int>::iterator end, int val);
void insertAlgo2(std::deque<std::pair<int, int > > myDeque, std::deque<int> *main_chain, int extraValue);
void sortInsideCoupleDeq(std::deque<std::pair<int, int > > *myDeque);
void mergeSortDeq(std::deque<std::pair<int, int > >::iterator start, std::deque<std::pair<int, int > >::iterator end, size_t size);
void couplesCreationDeq(std::deque<std::pair<int, int > > *myDeque, char **argv, int *additional_value);


// UTILS
void printBefore(char **argv);
bool compare(std::pair<int, int> x, std::pair<int, int> y);
void printAfterDeq(std::deque<int> main_chain);
void printAfter(std::list<int> main_chain);

#endif
