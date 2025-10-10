// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_RUNNER_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_RUNNER_HPP

#include <map>
#include <string_view>

class Test;
class Fixture;

class Runner
{
public:
    static Runner& get();

    int exec(int argc, const char* const argv[]);

    bool add(Fixture& fixture);
    bool add(std::string_view fixture_name, Test&& test);

private:
    Runner() = default;

    std::map<std::string_view, Fixture*> _fixtures;
};

#endif // K3_TOK3N_TESTS_FRAMEWORK_RUNNER_HPP
