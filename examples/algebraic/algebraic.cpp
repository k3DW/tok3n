#include "parser.h"
#include "print.h"

int main()
{
	auto result = input::parse("4 ^ (2 + 4 * 6) + 1 * 3");
	if (result)
		print(*result, 0);
	else
		std::cout << "Parse failure.\n";
}
