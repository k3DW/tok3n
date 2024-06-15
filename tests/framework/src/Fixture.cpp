#include "framework.h"
#include <iomanip>
#include <iostream>

void Fixture::add_test(Test& test)
{
	_tests.emplace(test.name(), &test);
}

int Fixture::run(std::ostream& os, const std::optional<std::string_view> test_name)
{
	if (!test_name.has_value())
	{
		os << "Running fixture " << std::quoted(_name) << "\n";
		int failures = 0;
		for (auto [_, test] : _tests)
		{
			failures += (test->run(os) == EXIT_SUCCESS) ? 0 : 1;
		}
		os << print_brief();
		os << "\n";
		return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
	}
	else
	{
		const auto it = _tests.find(*test_name);
		if (it == _tests.end())
		{
			os << "Error: Fixture " << std::quoted(_name) << " does not contain test " << std::quoted(*test_name) << "\n";
			return EXIT_FAILURE;
		}

		os << "Running fixture " << std::quoted(_name) << "\n";
		const auto out = it->second->run(os);
		os << print_brief();
		os << "\n";
		return out;
	}
}

std::string Fixture::print_brief() const
{
	StringBuilder builder;
	builder.append("Fixture \"", _name, "\" - ", _tests.size(), " tests / ", count_failures(), " failures.\n");
	return std::move(builder).build();
}

void Fixture::print_errors(std::ostream& os) const
{
	os << "Fixture " << std::quoted(_name) << "\n";
	for (auto [_, test] : _tests)
	{
		if (test->failed())
			os << test->print_errors();
	}
	os << "\n";
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

void Fixture::list(std::ostream& os) const
{
	for (auto [test_name, _] : _tests)
	{
		os
			<< std::quoted(_name)
			<< " - "
			<< std::quoted(test_name)
			<< "\n"
		;
	}
}
