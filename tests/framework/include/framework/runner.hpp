// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_RUNNER_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_RUNNER_HPP

#include <map>
#include <string_view>

namespace k3::testing {

class test;
class fixture;

class runner
{
public:
    static runner& get();

    int exec(int argc, const char* const argv[]);

    bool add(fixture& fixture);
    bool add(std::string_view fixture_name, test&& t);

private:
    runner() = default;

    std::map<std::string_view, fixture*> _fixtures;
};

} // namespace k3::testing

#endif // K3_TOK3N_TESTS_FRAMEWORK_RUNNER_HPP
