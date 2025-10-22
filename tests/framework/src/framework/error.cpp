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
        case both:
            return "Compile-time and run-time";
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

std::string tab_over(std::string str, const std::size_t spaces)
{
    str.insert(0, spaces, ' ');
    for (std::size_t pos = spaces; ;)
    {
        pos = str.find('\n', pos);
        if (std::string::npos == pos)
        {
            break;
        }
        ++pos;
        str.insert(pos, spaces, ' ');
        pos += spaces;
    }
    return str;
}

} // namespace

void print(std::ostream& os, const error& e)
{
    os << "[" << to_string(e.time) << " " << to_string(e.fatality) << " error]\n";
    for (const auto& loc : e.trace)
    {
        os << "    at " << loc.file_name() << ":" << loc.line() << "\n";
    }
    if (not e.message.empty())
    {
        os << tab_over(e.message, 4) << "\n";
    }
}

} // namespace k3::testing
