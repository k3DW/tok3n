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
	StringBuilder builder;
	builder.append("Displaying all fixture results, ", _fixtures.size(), " total.\n\n");

	std::vector<Fixture*> failed;

	for (auto [name, fixture] : _fixtures)
	{
		builder.append(fixture->print_brief());
		if (fixture->count_failures() != 0)
			failed.push_back(fixture);
	}

	for (auto* fixture : failed)
	{
		builder.append("\n=================================\n\n");
		builder.append(fixture->print_failures());
	}

	return std::move(builder).build();
}
