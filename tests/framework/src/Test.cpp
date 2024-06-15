#include "framework.h"
#include <iomanip>
#include <iostream>

int Test::run(std::ostream& os)
{
	TestResultContext test_context(_result);
	_run();

	print_brief(os);
	return failed() ? EXIT_FAILURE : EXIT_SUCCESS;
}

void Test::print_brief(std::ostream& os) const
{
	os
		<< "    Test " << std::quoted(_name) << " - "
		<< _result.checks << " checks / " << _result.errors.size() << " errors.\n";
}

void Test::print_errors(std::ostream& os) const
{
	auto& [message, location] = _result.errors.back();
	os << "Test " << std::quoted(_name) << " failed at\n";
	os << "    File: " << location.file_name() << "\n";
	os << "    Line: " << location.line() << "\n";
	os << "    Message: " << message << "\n";
}

bool Test::failed() const
{
	return not _result.errors.empty();
}
