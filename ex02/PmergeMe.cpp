#include "PmergeMe.hpp"

// LIST

void createMainChain(std::list<int> *main_chain, const std::list<std::pair<int, int>> &myList)
{
    for (std::list<std::pair<int, int>>::const_iterator it = myList.begin(); it != myList.end(); ++it)
        main_chain->push_back(it->second);

    // Vérifie avant d'ajouter pour éviter un doublon du premier élément
    if (!myList.empty() && std::find(main_chain->begin(), main_chain->end(), myList.begin()->first) == main_chain->end())
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
    
    // Vérifie que l'élément n'est pas déjà présent avant de l'insérer
    if (place_to_insert == main_chain->end() || *place_to_insert != val)
        main_chain->insert(place_to_insert, val);
}

/*
Uses std::lower_bound() to find the correct position
Efficiently inserts elements while keeping main_chain sorted
Main Chain: [3, 7, 8]
Insert 5 → [3, 5, 7, 8]
*/

void processJacobsthalInsertions(std::list<std::pair<int, int>> &myList, std::list<int> *main_chain)
{
    const size_t Jacobsthal[] = {1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765};
    int jacobIndex = 1;

    std::list<std::pair<int, int>>::iterator currentCouple;
    std::list<std::pair<int, int>>::iterator lastInsertCouple = myList.begin();

    while (Jacobsthal[jacobIndex] <= myList.size())
    {
        currentCouple = myList.begin();
        std::advance(currentCouple, Jacobsthal[jacobIndex] - 1);
        lastInsertCouple = currentCouple;

        int insertCounter = 0;
        while (Jacobsthal[jacobIndex] - insertCounter > Jacobsthal[jacobIndex - 1])
        {
            std::list<int>::iterator insertPos = std::find(main_chain->begin(), main_chain->end(), currentCouple->second);
            
            // Vérification pour éviter d'insérer en double
            if (std::find(main_chain->begin(), main_chain->end(), currentCouple->first) == main_chain->end())
                binarySearchInsertion(main_chain, insertPos, currentCouple->first);
            
            if (currentCouple == myList.begin()) break; // Éviter de décrémenter au-delà du début
            currentCouple--;
            insertCounter++;
        }
        jacobIndex++;
    }
}

void insertRemainingElements(std::list<std::pair<int, int>> &myList, std::list<int> *main_chain, std::list<std::pair<int, int>>::iterator lastInsertCouple)
{
    std::list<std::pair<int, int>>::iterator currentCouple = myList.end();
    if (currentCouple != myList.begin())
        currentCouple--;

    while (currentCouple != lastInsertCouple)
    {
        std::list<int>::iterator insertPos = std::find(main_chain->begin(), main_chain->end(), currentCouple->second);
        
        // Vérifie que l'élément n'est pas déjà présent
        if (std::find(main_chain->begin(), main_chain->end(), currentCouple->first) == main_chain->end())
            binarySearchInsertion(main_chain, insertPos, currentCouple->first);
        
        if (currentCouple == myList.begin()) break; // Éviter les erreurs de dépassement
        currentCouple--;
    }
}

void insertAlgo(std::list<std::pair<int, int>> myList, std::list<int> *main_chain, int extraValue)
{
    processJacobsthalInsertions(myList, main_chain);
    insertRemainingElements(myList, main_chain, myList.begin());

    // Vérifie avant d'insérer l'élément supplémentaire
    if (extraValue != -1 && std::find(main_chain->begin(), main_chain->end(), extraValue) == main_chain->end())
    {
        binarySearchInsertion(main_chain, main_chain->end(), extraValue);
    }
}

/*
  Jacobsthal sequence : Jn​=Jn−1​+2Jn−2
  determine insertion order
*/
