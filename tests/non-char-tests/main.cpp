#include "samples.h"
#include <iostream>

int main()
{
	auto& runner = Runner::get();
	runner.run();
	std::cout << runner.print_results();
}
