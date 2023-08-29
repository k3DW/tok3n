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
	builder.format("Displaying all fixture results, {} total.\n\n", _fixtures.size());

	for (auto [name, fixture] : _fixtures)
	{
		builder.append("=================================\n\n");
		builder.append(fixture->print_results());
	}

	return std::move(builder).build();
}
