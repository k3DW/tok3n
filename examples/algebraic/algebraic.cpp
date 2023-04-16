#include "parser.h"
#include "print.h"
#include "evaluate.h"

int main()
{
	auto result = input::parse("4 ^ (2 + 4 * 6) + 1 * 3");
	if (result)
	{
		print(*result, 0);
		std::cout << "\n" << evaluate(*result) << "\n";
	}
	else
		std::cout << "Parse failure.\n";
}
