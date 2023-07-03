#pragma once
#include "framework/Error.h"

class Test;

class TestResult
{
public:
	TestResult(const Test* test, std::vector<Error>&& errors)
		: _test(test)
		, _errors(std::move(errors))
	{}

	TestResult(const Test* test)
		: _test(test)
	{}
	
	bool has_errors() const { return not _errors.empty(); }

	const Test* test()   const { return _test; }
	const auto& errors() const { return _errors; }

private:
	const Test* _test;
	std::vector<Error> _errors;
};
