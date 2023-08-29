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

std::string Fixture::print_brief() const
{
	return std::format("Fixture \"{}\" - {} tests / {} failures.\n", _name, _tests.size(), count_failures());
}

std::string Fixture::print_failures() const
{
	StringBuilder builder;
	builder.format("Fixture \"{}\" - {} tests\n", _name, _tests.size());
	
	std::vector<Test*> failed;
	
	for (auto [name, test] : _tests)
	{
		builder.append(test->print_brief());
		if (test->failed())
			failed.push_back(test);
	}

	for (auto* test : failed)
	{
		builder.append("\n");
		builder.append(test->print_errors());
	}

	return std::move(builder).build();
}

size_t Fixture::count_failures() const
{
	std::size_t total = 0;
	for (auto& [name, test] : _tests)
	{
		if (test->failed())
			++total;
	}
	return total;
}
