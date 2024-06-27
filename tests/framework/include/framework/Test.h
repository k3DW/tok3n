#pragma once
#include <iosfwd>
#include <string>
#include <string_view>
#include "framework/Hash.h"

struct TestResult;

class Test
{
public:
	std::string_view name() const
	{
		return _name;
	}

	TestResult run(std::ostream& os) const;

protected:
	Test(std::string name)
		: _name(std::move(name))
	{}

private:
	std::string _name;

	virtual void _run() const = 0;
};



template <std::size_t hash>
class TestImpl {};

#define TEST(FIXTURE_NAME, NAME)                                              \
	template <>                                                               \
	class TestImpl<test_hash(FIXTURE_NAME, NAME)> : private Test              \
	{                                                                         \
	private:                                                                  \
		static_assert(                                                        \
			std::is_base_of_v<Fixture, FixtureImpl<test_hash(FIXTURE_NAME)>>, \
			"Fixture \"" FIXTURE_NAME "\" has not been declared.");           \
		TestImpl() : Test(NAME) {}                                            \
		static const Test& _self;                                             \
		void _run() const override;                                           \
	};                                                                        \
	const Test& TestImpl<test_hash(FIXTURE_NAME, NAME)>::_self                \
		= Runner::get().add(FIXTURE_NAME, []() -> auto&                       \
		{ static TestImpl<test_hash(FIXTURE_NAME, NAME)> t; return t; }());   \
	void TestImpl<test_hash(FIXTURE_NAME, NAME)>::_run() const
