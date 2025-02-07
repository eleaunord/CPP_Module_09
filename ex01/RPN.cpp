#include "RPN.hpp"
#include <iostream>
#include <sstream>
#include <stack>
#include <climits>  
#include <cstdlib> 

#ifndef INT_MAX
    #define INT_MAX 2147483647
#endif
#ifndef INT_MIN
    #define INT_MIN (-2147483647 - 1)
#endif

static long calculate(long upper, long lower, char operation)
{
    if (operation == '+')
    {
        if ((lower > 0 && upper > LONG_MAX - lower) || (lower < 0 && upper < LONG_MIN - lower))
            throw std::overflow_error("Error: Overflow in addition");
        return upper + lower;
    }
    else if (operation == '-')
    {
        if ((lower < 0 && upper > LONG_MAX + lower) || (lower > 0 && upper < LONG_MIN + lower))
            throw std::overflow_error("Error: Overflow in subtraction");
        return upper - lower;
    }
    else if (operation == '*')
    {
        if (upper != 0 && (lower > LONG_MAX / upper || lower < LONG_MIN / upper))
            throw std::overflow_error("Error: Overflow in multiplication");
        return upper * lower;
    }
    else if (operation == '/')
    {
        if (lower == 0)
            throw std::runtime_error("Error: Division by zero");
        if (upper == LONG_MIN && lower == -1)
            throw std::overflow_error("Error: Overflow in division");
        return upper / lower;
    }
    throw std::runtime_error("Error: Invalid operator");
}


static void processToken(std::stack<long> &stack, const std::string &token)
{
    if (token.length() != 1 && !isdigit(token[0]) && token[0] != '-')
        throw std::runtime_error("Error: Invalid token");

    if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-'))
    {
        char *end;
        long num = std::strtol(token.c_str(), &end, 10); 
        if (*end != '\0')
            throw std::runtime_error("Error: Invalid number format");
        stack.push(num);
    }
    else
    {
        if (stack.size() < 2)
            throw std::runtime_error("Error: Not enough numbers");

        long lower = stack.top();
        stack.pop();
        long upper = stack.top();
        stack.pop();

        long result = calculate(upper, lower, token[0]);

        stack.push(result);
    }
}


int RPN(const std::string &equation)
{
    std::stack<long> stack;
    std::stringstream flux(equation);
    std::string token;

    while (flux >> token)
    {
        processToken(stack, token);
    }

    if (stack.size() != 1)
        throw std::runtime_error("Error: Too many numbers");

    long result = stack.top();
    if (result > INT_MAX || result < INT_MIN)
        throw std::overflow_error("Error: Result out of int range");

    return static_cast<int>(result);
}
