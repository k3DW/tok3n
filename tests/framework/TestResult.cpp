#include "pch.h"

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
	_current_result->errors.emplace_back(message, std::move(location));
}

bool TestResultContext::check(bool condition)
{
	_current_result->checks++;
	return condition;
}
