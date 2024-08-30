#include "framework.h"
#include <iomanip>
#include <iostream>

TestResult Test::run(std::ostream& os) const
{
	TestResult result(_name);
	{
		TestResultContext context(result);
		_func();
	}
	result.print_brief(os);
	return result;
}
