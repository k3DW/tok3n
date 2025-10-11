// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include <iomanip>
#include <iostream>

void TestResult::print_brief(std::ostream& os) const
{
    os
        << "    Test " << std::quoted(name) << " - "
        << checks << " checks / " << errors.size()
        << " error" << (errors.size() == 1 ? "" : "s") << ".\n";
}

void TestResult::print_errors(std::ostream& os) const
{
    os << "Test " << std::quoted(name) << " failed with "
        << errors.size() << " error" << (errors.size() == 1 ? "" : "s") << ".\n";
    for (const Error& error : errors)
    {
        print(os, error);
    }
}

void FixtureResult::push_back(TestResult&& result)
{
    if (result.errors.empty())
        passes.push_back(std::move(result));
    else
        failures.push_back(std::move(result));
}

void FixtureResult::print_brief(std::ostream& os) const
{
    os
        << "Fixture " << std::quoted(name) << " - "
        << (passes.size() + failures.size()) << " tests / "
        << failures.size() << " failures.\n\n";
}

void FixtureResult::print_errors(std::ostream& os) const
{
    os << "Fixture " << std::quoted(name) << "\n";
    for (const TestResult& result : failures)
    {
        result.print_errors(os);
    }
    os << "\n";
}

TestResultContext::TestResultContext(TestResult& result)
    : _old_result(_current_result)
{
    _current_result = &result;
}

TestResultContext::~TestResultContext()
{
    _current_result = _old_result;
}

void TestResultContext::add_error(bool ct, bool rt, std::string message, Error::Fatality fatality, std::source_location location)
{
    if (not ct)
        _current_result->errors.emplace_back(Error::Time::compile_time, fatality, std::move(message), std::move(location));
    if (not rt)
        _current_result->errors.emplace_back(Error::Time::run_time, fatality, std::move(message), std::move(location));
}

bool TestResultContext::check(bool condition)
{
    _current_result->checks++;
    return condition;
}
