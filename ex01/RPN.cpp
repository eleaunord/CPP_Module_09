#include "RPN.hpp"

/*
Opération d'une pile stack (std::stack) (last in first out logic)

	top() = renvoie dernier élément ajouté à la liste sans le retirer
	pop() = supprime l'élement situé au sommet de la pile (ne renvoie pas la valeur suppr donc utiliser top() pour d'abord avoir la valeur)
	push() = ajouter un nouvel élément au sommet de la pile
*/

// arithmetic operations : upper and lower elements
static int calculate(int upper, int lower, char operation)
{
	if (operation == '+')
		return upper + lower; 
	else if (operation == '-')
		return upper - lower;
	else if (operation == '*')
		return upper * lower;
	else if (operation == '/')
	{
		if (lower == 0)
			throw std::runtime_error("Error: Division by zero");
		return upper / lower;
	}
	throw std::runtime_error("Error: Invalid operator"); // for eg a %
}


// traite chaque element de l'expression RPN 
static void processToken(std::stack<int> &stack, const std::string &token)
{
	if (token.length() != 1)
		throw std::runtime_error("Error");

	if (isdigit(token[0]))
	{
		stack.push(atoi(token.c_str())); // conversion en int + ajoute à la pile
	}
	else // aka si on a un operateur (du moins c'est ce qu'on att)
	{
		if (stack.size() < 2)
			throw std::runtime_error("Error: Not enough numbers");

		int lower = stack.top(); 
		stack.pop();
		int upper = stack.top();
		stack.pop();

		stack.push(calculate(upper, lower, token[0]));
	}
}

// parse expression
int RPN(const std::string &equation)
{
	std::stack<int> stack; 
	std::stringstream flux(equation); // stream de chaîne à partir de la chaîne donnée
	std::string token;

	while (flux >> token)
	{
		processToken(stack, token);
	}
	// une fois qu'on a tout il devrait rester juste le résultat finale sinon erreur
	if (stack.size() != 1)
		throw std::runtime_error("Operand Error");

	return stack.top();
}
