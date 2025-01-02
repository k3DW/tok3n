// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_TESTRESULT_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_TESTRESULT_HPP

#include <iosfwd>
#include <string_view>
#include <vector>

struct Error;

struct TestResult
{
	TestResult(std::string_view name)
		: name(name) {}

	std::string_view name;
	std::size_t checks = 0;
	std::vector<Error> errors{};

	void print_brief(std::ostream& os) const;
	void print_errors(std::ostream& os) const;
};

struct FixtureResult
{
	FixtureResult(std::string_view name)
		: name(name) {}

	std::string_view name;
	std::vector<TestResult> passes;
	std::vector<TestResult> failures;

	void push_back(TestResult&& result);
	void print_brief(std::ostream& os) const;
	void print_errors(std::ostream& os) const;
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

#endif // K3_TOK3N_TESTS_FRAMEWORK_TESTRESULT_HPP
