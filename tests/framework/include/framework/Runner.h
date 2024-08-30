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
