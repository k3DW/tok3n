// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "framework.hpp"
#include "framework/runner.hpp"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <optional>

namespace k3::testing {

runner& runner::get()
{
    static runner r;
    return r;
}

bool runner::add(fixture& fixture)
{
    _fixtures.emplace(fixture.name(), &fixture);
    return true;
}

bool runner::add(std::string_view fixture_name, test&& t)
{
    _fixtures.at(fixture_name)->add_test(std::move(t));
    return true;
}

int runner::exec(const int argc, const char* const argv[])
{
    const std::vector<std::string_view> args(argv, argv + argc);

    if (args.size() == 1)
    {
        goto RUN_ALL_TESTS;
    }

    if (args[1] == "--help")
    {
        std::cout <<
            "`<no-args>` => Same as `run`\n"
            "`list` => List all tests\n"
            "`list` \"<file>\" => List all tests and output to the file\n"
            "`run` => Run all tests\n"
            "`run \"<fixture>\" => Run all tests in the given fixture\n"
            "`run \"<fixture>\" \"<test>\" => Run the given test\n"
        ;
        return EXIT_SUCCESS;
    }
    else if (args[1] == "run")
    {
        if (args.size() > 4)
        {
            std::cout << "Error: Too many arguments to `run` command. Use --help for more info.\n";
            return EXIT_FAILURE;
        }
        else if (args.size() == 2)
        {
RUN_ALL_TESTS:
            std::vector<fixture_result> passes;
            std::vector<fixture_result> failures;
            std::size_t total_test_failures = 0;
            for (auto [_, fixture] : _fixtures)
            {
                fixture_result result = fixture->run(std::cout);
                total_test_failures += result.failures.size();
                if (result.failures.empty())
                    passes.push_back(std::move(result));
                else
                    failures.push_back(std::move(result));
            }

            if (failures.empty())
            {
                std::cout
                    << "================================\n\n"
                    << "All tests passed.\n";
                return EXIT_SUCCESS;
            }
            else
            {
                std::cout
                    << "================================\n\n"
                    << total_test_failures << " test" << (total_test_failures == 1 ? "" : "s") << " failed.\n\n";
                for (const fixture_result& result : failures)
                {
                    result.print_errors(std::cout);
                }
                return EXIT_FAILURE;
            }
        }
        else
        {
            const auto it = _fixtures.find(args[2]);
            if (it == _fixtures.end())
            {
                std::cout << "Error: Fixture " << std::quoted(args[2]) << " does not exist.\n";
                return EXIT_FAILURE;
            }

            fixture* const f = it->second;
            const fixture_result result = (args.size() == 3)
                ? f->run(std::cout)
                : f->run(std::cout, args[3]);

            if (result.failures.empty())
            {
                std::cout
                    << "================================\n\n"
                    << "All tests passed.\n";
                return EXIT_SUCCESS;
            }
            else
            {
                std::cout
                    << "================================\n\n"
                    << result.failures.size() << " test" << (result.failures.size() == 1 ? "" : "s") << " failed.\n\n";
                result.print_errors(std::cout);
                return EXIT_FAILURE;
            }
        }
    }
    else if (args[1] == "list")
    {
        if (args.size() > 3)
        {
            std::cout << "Error: Too many arguments to `list` command. Use --help for more info.\n";
            return EXIT_FAILURE;
        }

        std::optional<std::ofstream> file = std::nullopt;
        if (args.size() == 3)
        {
            file.emplace();
            file->open(args[2].data());
            if (!file->is_open())
            {
                std::cout << "Error: Could not open file - " << args[2] << "\n";
                return EXIT_FAILURE;
            }
        }

        std::ostream& stream = (file.has_value()) ? *file : std::cout;
        for (auto [name, fixture] : _fixtures)
        {
            fixture->list(stream);
        }
        return EXIT_SUCCESS;
    }
    else
    {
        std::cout << "Error: Unrecognized argument. Use --help for more info.\n";
        return EXIT_FAILURE;
    }
}

} // namespace k3::testing
