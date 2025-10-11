// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include <iostream>

static std::string_view to_string(Error::Time time)
{
    using enum Error::Time;
    switch (time)
    {
    case compile_time: return "Compile-time";
    case run_time: return "Run-time";
    default: return "<Invalid Error::Time>";
    }
}

static std::string_view to_string(Error::Fatality fatality)
{
    using enum Error::Fatality;
    switch (fatality)
    {
    case non_fatal: return "non-fatal";
    case fatal: return "fatal";
    default: return "<Invalid Error::Fatality>";
    }
}

void print(std::ostream& os, const Error& error)
{
    os << "[" << to_string(error.time) << " " << to_string(error.fatality) << " error]\n";
    os << "    Message: " << error.message << "\n";
    os << "    File: " << error.location.file_name() << "\n";
    os << "    Line: " << error.location.line() << "\n";
}
