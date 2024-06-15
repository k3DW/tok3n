#include "samples.h"
#include <iostream>

int main(int argc, const char* argv[])
{
	auto& runner = Runner::get();
	return runner.exec(argc, argv);
}
