#include "framework.h"

TestResultContext::TestResultContext(TestResult& result)
	: _old_result(_current_result)
{
	_current_result = &result;
}

TestResultContext::~TestResultContext()
{
	_current_result = _old_result;
}

void TestResultContext::add_error(std::string_view message, std::source_location location)
{
	_current_result->errors.emplace_back(Error::Time::run_time, Error::Fatality::fatal, message, std::move(location));
}

bool TestResultContext::check(bool condition)
{
	_current_result->checks++;
	return condition;
}
