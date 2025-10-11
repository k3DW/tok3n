// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
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
