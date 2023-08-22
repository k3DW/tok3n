#include "pch.h"

void Fixture::add_test(Test& test)
{
	_tests.emplace(test.name(), &test);
}

void Fixture::run()
{
	for (auto& [_, test] : _tests)
	{
		test->run();
	}
}

std::string Fixture::print_results() const
{
	std::vector<std::string> strings;
	strings.push_back(std::format("Fixture \"{}\" - {} tests\n\n", _name, _tests.size()));

	for (auto& [_, test] : _tests)
	{
		strings.push_back(test->print_results());
		strings.push_back("\n");
	}

	const size_t total = std::reduce(strings.begin(), strings.end(), size_t{ 0 }, [](size_t ac, const std::string& str) { return ac + str.size(); });
	std::string out;
	out.reserve(total);

	for (const std::string& str : strings)
		out.insert(out.end(), str.begin(), str.end());
	return out;
}
