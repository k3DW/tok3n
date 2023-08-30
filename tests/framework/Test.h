#pragma once
#include <string>
#include <string_view>
#include <k3/tok3n/types/StaticString.h>
#include "framework/TestResult.h"

class Test
{
public:
	std::string_view name() const
	{
		return _name;
	}

	void run();
	std::string print_brief() const;
	std::string print_errors() const;
	bool failed() const;

protected:
	Test(std::string name)
		: _name(std::move(name))
	{}

private:
	std::string _name;

	TestResult _result{};

	virtual void _run() = 0;
};



template <k3::tok3n::StaticString, k3::tok3n::StaticString>
class TestImpl {};

#define TEST(FIXTURE_NAME, NAME)                                             \
	template <>                                                              \
	class TestImpl<FIXTURE_NAME, NAME> : public Test                         \
	{                                                                        \
	private:                                                                 \
		static_assert(std::is_base_of_v<Fixture, FixtureImpl<FIXTURE_NAME>>, \
			"Fixture \"" FIXTURE_NAME "\" has not been declared.");          \
		TestImpl() : Test(NAME) {}                                           \
		static const Test& _self;                                            \
		void _run() override;                                                \
	};                                                                       \
	const Test& TestImpl<FIXTURE_NAME, NAME>::_self                          \
		= Runner::get().add(FIXTURE_NAME, []() -> auto&                      \
		{ static TestImpl<FIXTURE_NAME, NAME> t; return t; }());             \
	void TestImpl<FIXTURE_NAME, NAME>::_run()
