// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_ERROR_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_ERROR_HPP

#include <source_location>
#include <string_view>
#include <string>
#include <vector>

namespace k3::testing {

enum class error_time
{
    compile_time,
    run_time,
    both,
};

enum class error_fatality
{
    non_fatal,
    fatal,
};

struct error
{
    explicit error(error_time time_, error_fatality fatality_, std::vector<std::source_location> trace_)
        : time(time_), fatality(fatality_), trace(std::move(trace_))
    {}
    error_time time;
    error_fatality fatality;
    std::string message{};
    std::vector<std::source_location> trace;
};

void print(std::ostream& os, const error& e);

} // namespace k3::testing

#endif // K3_TOK3N_TESTS_FRAMEWORK_ERROR_HPP
