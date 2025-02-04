#include "PmergeMe.hpp"

/*
	Trier une séquence d'entiers positifs en utilisant l'algorithme merge-insert sort
(basé sur l'algo Ford-Johnson)
std::vector et std::deque à utiliser
3000 entiers
pas d'algo de tri standard (std::sort)
affiche sequence initiale et sequence trié

algorithme Ford-Johnson = algo de tri optimisé qui combine tri par fusion (merge sort )
et tri par insertion (insert sort)

1/ découper séquence en couples (si taille impaire garder élément seul)
2/ trier paires individuellements ordre croissant
3/ deux sous-listes : "max" et "min"
	- Prends le plus grand élément de chaque paire et mets-le dans une liste ("max").
	- Prends le plus petit élément de chaque paire et mets-le dans une autre liste ("min").
4/ trier récursivement la liste "max"
5/ insérer elements liste min dans la bonne pos dans la liste triée max en utilisant un algo d'insertion
6/ combiner deux listes


*/

void printBefore(char **argv)
{
	int i = 1;
	int errorFlag = 0;
	std::ostringstream output;

	while (argv[i])
	{
		std::string input = argv[i];

		// we need to check if the input is too large or negative ; extra input.size() > 10 check for "9999999999"
		if (input.size() > 10 || std::atol(input.c_str()) > INT_MAX || std::atol(input.c_str()) < 0)
			errorFlag = 1;

		for (size_t j = 0; j < input.size(); j++)
		{
			if (!isdigit(input[j]))
				errorFlag = 1;
		}

		output << input << " "; // string stream
		i++;
	}

	if (errorFlag == 1)
		throw PmergException("Error");

	std::cout << "Before: " << output.str() << "\n";
}

void printAfter(std::list<int> main_chain)
{
	std::cout << "After: ";
	for (std::list<int>::iterator it = main_chain.begin(); it != main_chain.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << '\n';
}

void printAfterDeq(std::deque<int> main_chain)
{
	std::cout << "After: ";
	for (std::deque<int>::iterator it = main_chain.begin(); it != main_chain.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << '\n';
}
