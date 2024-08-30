#pragma once
#include <iosfwd>
#include <string>
#include <string_view>
#include "framework/Hash.h"

struct TestResult;

template <std::size_t hash>
class TestImpl {};

class Test
{
public:
	std::string_view name() const
	{
		return _name;
	}
	
	TestResult run(std::ostream& os) const;

private:
	template <std::size_t hash>
	friend class TestImpl;

	using func_type = void(*)();

	template <std::size_t N>
	Test(const char(&name)[N], func_type func)
		: _name(name), _func(func) {}

	std::string_view _name; // This is fine because we only construct with a string literal
	func_type _func;
};




#define TEST(FIXTURE_NAME, NAME)                                              \
	template <>                                                               \
	class TestImpl<test_hash(FIXTURE_NAME, NAME)>                             \
	{                                                                         \
	private:                                                                  \
		static_assert(                                                        \
			std::is_base_of_v<Fixture, FixtureImpl<test_hash(FIXTURE_NAME)>>, \
			"Fixture \"" FIXTURE_NAME "\" has not been declared.");           \
		static void _run();                                                   \
		static inline const bool _init =                                      \
			Runner::get().add(FIXTURE_NAME, Test(NAME, &_run));               \
	};                                                                        \
	void TestImpl<test_hash(FIXTURE_NAME, NAME)>::_run()
