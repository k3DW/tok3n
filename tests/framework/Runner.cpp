#include "pch.h"

Runner& Runner::get()
{
	static Runner runner;
	return runner;
}

Fixture& Runner::add(Fixture& fixture)
{
	_fixtures.emplace(fixture.name(), &fixture);
	return fixture;
}

Test& Runner::add(std::string_view fixture_name, Test& test)
{
	_fixtures.at(fixture_name)->add_test(test);
	return test;
}

void Runner::run()
{
	for (auto [name, fixture] : _fixtures)
	{
		fixture->run();
	}
}

std::string Runner::print_results() const
{
	std::vector<std::string> strings;
	strings.push_back(std::format("Displaying all fixture results, {} total.\n\n", _fixtures.size()));

	for (auto [name, fixture] : _fixtures)
	{
		strings.push_back("=================================\n\n");
		strings.push_back(fixture->print_results());
	}

	const size_t total = std::reduce(strings.begin(), strings.end(), size_t{ 0 }, [](size_t ac, const std::string& str) { return ac + str.size(); });
	std::string out;
	out.reserve(total);

	for (const std::string& str : strings)
		out.insert(out.end(), str.begin(), str.end());
	return out;
}
