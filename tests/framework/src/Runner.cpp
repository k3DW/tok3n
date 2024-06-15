#include "framework.h"
#include <iomanip>
#include <iostream>

Runner& Runner::get()
{
	static Runner runner;
	return runner;
}

Fixture& Runner::add(Fixture& fixture)
{
	_fixtures.emplace(fixture.name(), &fixture);
	return fixture;
}

Test& Runner::add(std::string_view fixture_name, Test& test)
{
	_fixtures.at(fixture_name)->add_test(test);
	return test;
}

int Runner::exec(const int argc, const char* const argv[])
{
	const std::vector<std::string_view> args(argv, argv + argc);

	if (args.size() == 1)
	{
		goto RUN_ALL_TESTS;
	}

	if (args[1] == "--help")
	{
		std::cout <<
			"`<no-args>` => Same as `run`"
			"`list` => List all tests\n"
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
			int failures = 0;
			for (auto [_, fixture] : _fixtures)
			{
				failures += (fixture->run(std::cout) == EXIT_SUCCESS) ? 0 : 1;
			}

			if (failures == 0)
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
					<< failures << " tests failed.\n\n";
				for (auto [_, fixture] : _fixtures)
				{
					if (fixture->count_failures() != 0)
					{
						fixture->print_errors(std::cout);
					}
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

			Fixture* const fixture = it->second;
			const int code = (args.size() == 3)
				? fixture->run(std::cout)
				: fixture->run(std::cout, args[3]);

			if (code == EXIT_SUCCESS)
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
					<< fixture->count_failures() << " tests failed.\n\n";
				fixture->print_errors(std::cout);
				return EXIT_FAILURE;
			}
		}
	}
	else if (args[1] == "list")
	{
		if (args.size() != 2)
		{
			std::cout << "Error: `list` command takes no additional arguments. Use --help for more info.\n";
			return EXIT_FAILURE;
		}
		for (auto [name, fixture] : _fixtures)
		{
			fixture->list(std::cout);
		}
		return EXIT_SUCCESS;
	}
	else
	{
		std::cout << "Error: Unrecognized argument. Use --help for more info.\n";
		return EXIT_FAILURE;
	}
}
