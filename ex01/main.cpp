#include "RPN.hpp"
#include <limits>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage : ./RPN \"<expression>\"\n";
		return 1;
	}

	try
	{
		int result = RPN(argv[1]);

		std::cout << result << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
