#include "pch.h"

void Test::run()
{
	TestResultContext test_context(_result);
	_run();
}

std::string Test::print_results() const
{
	auto& [checks, errors] = _result;

	if (errors.empty())
	{
		return std::format(
			"Test \"{}\"\n"
			"  Passed! Checked {} conditions.\n"
		, _name, checks);
	}
	else
	{
		auto& [message, location] = errors.back();
		return std::format(
			"Test \"{}\"\n"
			"  Failed.\n"
			"    File: {}\n"
			"    Line: {}\n"
			"    Message: {}\n"
			"  {} total errors. Checked {} conditions.\n"
		, _name, location.file_name(), location.line(), message, errors.size(), checks);
	}
}
