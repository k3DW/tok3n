#pragma once
#include "framework/Test.h"
#include "framework/FixtureResult.h"
#include "framework/TestResult.h"
#include <map>

class Fixture
{
public:
	Fixture(std::string_view name)
		: _name(name)
	{}

	[[nodiscard]] FixtureResult run()
	{
		FixtureResult result(this);

		for (Test* test : _tests)
		{
			TestResult r = test->run();
			if (r.has_errors())
				result.add_failure(std::move(r));
			else
				result.add_success(std::move(r));
		}
		
		return result;
	}

	[[nodiscard]] static FixtureResults run_all()
	{
		FixtureResults results;

		for (auto& [_, fixture] : _all_fixtures)
		{
			FixtureResult r = fixture.run();
			if (r.has_errors())
				results.add_failure(std::move(r));
			else
				results.add_success(std::move(r));
		}

		return results;
	}

	std::string_view name() const
	{
		return _name;
	}

	static void add_test_to_fixture(Test* test, std::string_view fixture_name)
	{
		auto it = _all_fixtures.find(fixture_name);
		if (it != _all_fixtures.end())
		{
			it->second._tests.push_back(test);
		}
		else
		{
			auto [emplace_it, _] = _all_fixtures.emplace(fixture_name, fixture_name);
			emplace_it->second._tests.push_back(test);
		}
	}

private:
	std::string _name;
	std::vector<Test*> _tests;

	static inline std::map<std::string, Fixture, std::less<>> _all_fixtures;
};
