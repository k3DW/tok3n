// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include <iomanip>
#include <iostream>

void Fixture::add_test(Test&& test)
{
    _tests.emplace(test.name(), std::move(test));
}

FixtureResult Fixture::run(std::ostream& os) const
{
    os << "Running fixture " << std::quoted(_name) << "\n";

    FixtureResult result(_name);
    for (const auto& [_, test] : _tests)
    {
        result.push_back(test.run(os));
    }
    result.print_brief(os);
    return result;
}

FixtureResult Fixture::run(std::ostream& os, std::string_view test_name) const
{
    FixtureResult result(_name);

    const auto it = _tests.find(test_name);
    if (it == _tests.end())
    {
        os << "Error: Fixture " << std::quoted(_name) << " does not contain test " << std::quoted(test_name) << "\n";
        return result;
    }

    os << "Running fixture " << std::quoted(_name) << "\n";
    result.push_back(it->second.run(os));
    result.print_brief(os);
    return result;
}

void Fixture::list(std::ostream& os) const
{
    for (const auto& [test_name, _] : _tests)
    {
        os
            << std::quoted(_name)
            << " - "
            << std::quoted(test_name)
            << "\n"
        ;
    }
}
