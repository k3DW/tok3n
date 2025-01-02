// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"
#include <iostream>

int main(int argc, const char* argv[])
{
	auto& runner = Runner::get();
	return runner.exec(argc, argv);
}
