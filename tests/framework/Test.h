#pragma once
#include "framework/Error.h"
#include "framework/TestResult.h"
#include <string>
#include <vector>

class Test
{
public:
	Test(std::string_view fixture_name, std::string name);

	[[nodiscard]] TestResult run()
	{
		_errors.clear();
		_run();
		if (_errors.empty())
			return TestResult(this);
		else
			return TestResult(this, std::move(_errors));
	}

	std::string_view name() const
	{
		return _name;
	}

private:
	std::string _name;
	std::vector<Error> _errors;

	virtual void _run() = 0;

protected:
	bool Assert(bool condition, std::string_view message, std::source_location location = std::source_location::current())
	{
		if (not condition)
			_errors.emplace_back(message, std::move(location));
		return condition;
	}
};

#include "framework/Fixture.h"

inline Test::Test(std::string_view fixture_name, std::string name)
	: _name(std::move(name))
{
	Fixture::add_test_to_fixture(this, fixture_name);
}



template <k3::tok3n::StaticString fixture, k3::tok3n::StaticString test>
class TestOverride {};

#define TEST(FIXTURE, NAME)                            \
	template <>                                        \
	class TestOverride<#FIXTURE, #NAME> : Test         \
	{                                                  \
		TestOverride() : Test(#FIXTURE, #NAME) {}      \
		void _run() override;                          \
		class Initializer;                             \
	};                                                 \
	class TestOverride<#FIXTURE, #NAME>::Initializer   \
	{                                                  \
		static inline TestOverride<#FIXTURE, #NAME> _; \
	};                                                 \
	void TestOverride<#FIXTURE, #NAME>::_run()



#define DISABLE_STATIC_ASSERT

#ifdef DISABLE_STATIC_ASSERT
#define STATIC_ASSERT(...)
#else
#define STATIC_ASSERT(...) static_assert(__VA_ARGS__)
#endif

#define ASSERT(CONDITION, MESSAGE)             \
	[&]() -> bool {                            \
		STATIC_ASSERT((CONDITION), MESSAGE);   \
		return Assert((CONDITION), (MESSAGE)); \
	}()
