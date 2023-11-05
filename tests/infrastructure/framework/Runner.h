#pragma once
#include <map>
#include <string>
#include <string_view>

class Test;
class Fixture;

class Runner
{
public:
	static Runner& get();

	void run();
	std::string print_results() const;

	Fixture& add(Fixture& fixture);
	Test& add(std::string_view fixture_name, Test& test);

protected:
	Runner() = default;

	std::map<std::string_view, Fixture*> _fixtures;
};
