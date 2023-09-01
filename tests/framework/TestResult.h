#pragma once
#include "framework/Error.h"

struct TestResult
{
	std::size_t checks = 0;
	std::vector<Error> errors{};
};

class TestResultContext
{
public:
	[[nodiscard]] TestResultContext(TestResult& result);

	~TestResultContext();

	TestResultContext(const TestResultContext&) = delete;
	TestResultContext(TestResultContext&&) = delete;
	TestResultContext& operator=(const TestResultContext&) = delete;
	TestResultContext& operator=(TestResultContext&&) = delete;

	static void add_error(std::string_view message, std::source_location location = std::source_location::current());

	static bool check(bool condition);

private:
	static inline TestResult* _current_result = nullptr;
	TestResult* _old_result;
};
