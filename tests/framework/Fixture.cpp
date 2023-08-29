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
	StringBuilder builder;
	builder.format("Fixture \"{}\" - {} tests\n\n", _name, _tests.size());

	for (auto& [_, test] : _tests)
	{
		builder.append(test->print_results());
		builder.append("\n");
	}

	return std::move(builder).build();
}
