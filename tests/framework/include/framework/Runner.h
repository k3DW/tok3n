// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <map>
#include <string_view>

class Test;
class Fixture;

class Runner
{
public:
	static Runner& get();

	int exec(int argc, const char* const argv[]);

	Fixture& add(Fixture& fixture);
	bool add(std::string_view fixture_name, Test&& test);

private:
	Runner() = default;

	std::map<std::string_view, Fixture*> _fixtures;
};
