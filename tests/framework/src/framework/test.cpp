// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include <iomanip>
#include <iostream>

namespace k3::testing {

test_result test::run(std::ostream& os) const
{
    test_result result(_name);
    {
        test_result_context context(result);
        _func();
    }
    result.print_brief(os);
    return result;
}

} // namespace k3::testing
