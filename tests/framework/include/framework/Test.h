#pragma once
#include <iosfwd>
#include <string>
#include <string_view>
#include <k3/tok3n/types/StaticArray.h>
#include "framework/TestResult.h"

class Test
{
public:
	std::string_view name() const
	{
		return _name;
	}

	int run(std::ostream& os);

	void print_brief(std::ostream& os) const;
	void print_errors(std::ostream& os) const;
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



template <k3::tok3n::StaticArray fixture_name, k3::tok3n::StaticArray name>
requires std::same_as<char, typename decltype(fixture_name)::value_type>
	 and std::same_as<char, typename decltype(name)::value_type>
class TestImpl {};

#define TEST_(FIXTURE_NAME, NAME)                                            \
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

#define TEST(FIXTURE_NAME, NAME) TEST_(FIXTURE_NAME, NAME)
