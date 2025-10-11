// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include <iostream>

namespace k3::testing {

namespace {

std::string_view to_string(error_time time)
{
    using enum error_time;
    switch (time)
    {
        case compile_time:
            return "Compile-time";
        case run_time:
            return "Run-time";
        default:
            return "<Invalid error time>";
    }
}

std::string_view to_string(error_fatality fatality)
{
    using enum error_fatality;
    switch (fatality)
    {
        case non_fatal:
            return "non-fatal";
        case fatal:
            return "fatal";
        default:
            return "<Invalid error fatality>";
    }
}

} // namespace

void print(std::ostream& os, const error& e)
{
    os << "[" << to_string(e.time) << " " << to_string(e.fatality) << " error]\n";
    os << "    Message: " << e.message << "\n";
    os << "    File: " << e.location.file_name() << "\n";
    os << "    Line: " << e.location.line() << "\n";
}

} // namespace k3::testing
