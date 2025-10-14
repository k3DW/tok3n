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
        << checks << " checks / " << errors.size()
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
    os
        << "Fixture " << std::quoted(name) << " - "
        << (passes.size() + failures.size()) << " tests / "
        << failures.size() << " failures.\n\n";
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

context::message_streaming_context context::add_error(bool ct, bool rt, error_fatality fatality, std::source_location location)
{
    if (ct and rt)
    {
        throw std::logic_error("At least one of ct or rt must be false.");
    }

    std::vector<std::source_location> trace;
    trace = _trace;
    trace.push_back(std::move(location));

    const error_time time =
        (not ct and not rt) ? error_time::both :
        (not ct) ? error_time::compile_time : error_time::run_time;
    error& e = _current_result->errors.emplace_back(time, fatality, std::move(trace));
    return message_streaming_context{e.message};
}

bool context::check(bool condition)
{
    ++_current_result->checks;
    return condition;
}

} // namespace k3::testing
