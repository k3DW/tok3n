#include "pch.h"

void Test::run()
{
	TestResultContext test_context(_result);
	_run();
}

std::string Test::print_brief() const
{
	return std::format("    Test \"{}\" - {} checks / {} errors.\n", _name, _result.checks, _result.errors.size());
}

std::string Test::print_errors() const
{
	auto& [message, location] = _result.errors.back();
	return std::format(
		"Test \"{}\" failed at\n"
		"    File: {}\n"
		"    Line: {}\n"
		"    Message: {}\n"
		, _name, location.file_name(), location.line(), message);
}

bool Test::failed() const
{
	return not _result.errors.empty();
}
