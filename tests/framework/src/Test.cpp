#include "framework.h"
#include <iostream>

int Test::run(std::ostream& os)
{
	TestResultContext test_context(_result);
	_run();

	os << print_brief();
	return failed() ? EXIT_FAILURE : EXIT_SUCCESS;
}

std::string Test::print_brief() const
{
	StringBuilder builder;
	builder.append("    Test \"", _name, "\" - ", _result.checks, " checks / ", _result.errors.size(), " errors.\n");
	return std::move(builder).build();
}

std::string Test::print_errors() const
{
	auto& [message, location] = _result.errors.back();
	StringBuilder builder;
	builder.append("Test \"", _name, "\" failed at\n");
	builder.append("    File: ", location.file_name(), "\n");
	builder.append("    Line: ", location.line(), "\n");
	builder.append("    Message: ", message, "\n");
	return std::move(builder).build();
}

bool Test::failed() const
{
	return not _result.errors.empty();
}
