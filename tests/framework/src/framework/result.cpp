// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace k3::testing {

void test_result::print_brief(std::ostream& os) const
{
    os
        << "    Test " << std::quoted(name) << " - "
        << checks << " check" << (checks == 1 ? "" : "s") << " / " << errors.size()
        << " error" << (errors.size() == 1 ? "" : "s") << ".\n";
}

void test_result::print_errors(std::ostream& os) const
{
    os << "Test " << std::quoted(name) << " failed with "
        << errors.size() << " error" << (errors.size() == 1 ? "" : "s") << ".\n";
    for (const error& e : errors)
    {
        print(os, e);
    }
}

void fixture_result::push_back(test_result&& result)
{
    if (result.errors.empty())
        passes.push_back(std::move(result));
    else
        failures.push_back(std::move(result));
}

void fixture_result::print_brief(std::ostream& os) const
{
    const std::size_t num_tests = passes.size() + failures.size();
    os
        << "Fixture " << std::quoted(name) << " - "
        << num_tests << " test" << (num_tests == 1 ? "" : "s") << " / "
        << failures.size() << " failure" << (failures.size() == 1 ? "" : "s") << ".\n\n";
}

void fixture_result::print_errors(std::ostream& os) const
{
    os << "Fixture " << std::quoted(name) << "\n";
    for (const test_result& result : failures)
    {
        result.print_errors(os);
    }
    os << "\n";
}

context::test_result_context::test_result_context(test_result& result)
{
    if (_current_result != nullptr)
    {
        throw std::logic_error("Nested test_result_context is not allowed.");
    }
    _current_result = &result;
}

context::test_result_context::~test_result_context()
{
    _current_result = nullptr;
}

context::message_streaming_context context::add_error(check_result result, error_fatality fatality, std::source_location location)
{
    if (result)
    {
        throw std::logic_error("At least one of compile_time or run_time must be false.");
    }

    std::vector<std::source_location> trace;
    trace = _trace;
    trace.push_back(std::move(location));
    ++_total_errors;

    const error_time time =
        (not result.compile_time and not result.run_time) ? error_time::both :
        (not result.compile_time) ? error_time::compile_time : error_time::run_time;
    error& e = _current_result->errors.emplace_back(time, fatality, std::move(trace));
    return message_streaming_context{e.message};
}

check_result context::check(bool compile_time, bool run_time)
{
    ++_current_result->checks;
    return {
        .compile_time = compile_time,
        .run_time = run_time,
    };
}

std::size_t context::total_errors()
{
    return _total_errors;
}

} // namespace k3::testing
