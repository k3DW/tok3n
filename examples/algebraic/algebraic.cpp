// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "parser.hpp"
#include "print.hpp"
#include "evaluate.hpp"

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

	double a10 = evaluate(*input::parse("1 + 2 + 3 + 4"));
	double a4 = evaluate(*input::parse("1 + 2 - 3 + 4"));
	double a333 = evaluate(*input::parse("3^3^3"));
	
	std::cout << "\n" << a10;
	std::cout << "\n" << a4;
	std::cout << "\n" << a333;
}
