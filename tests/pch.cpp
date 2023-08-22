#include <iostream>
#include "pch.h"

int main()
{
	auto& runner = Runner::get();
	runner.run();
	std::cout << runner.print_results();
}
