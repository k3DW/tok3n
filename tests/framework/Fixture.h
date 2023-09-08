#pragma once
#include <string>
#include <string_view>
#include <unordered_map>
#include <k3/tok3n/types/StaticString.h>

class Test;

class Fixture
{
public:
	void add_test(Test& test);

	std::string_view name() const
	{
		return _name;
	}

	void run();
	std::string print_brief() const;
	std::string print_failures() const;
	std::size_t count_failures() const;

protected:
	Fixture(std::string name)
		: _name(std::move(name))
	{}

	virtual ~Fixture() = 0 {}

private:
	std::string _name;
	std::unordered_map<std::string_view, Test*> _tests;
};



template <k3::tok3n::StaticArray name>
requires std::same_as<char, typename decltype(name)::value_type>
class FixtureImpl {};

#define FIXTURE(NAME)                                \
	template <>                                      \
	class FixtureImpl<NAME> : public Fixture         \
	{                                                \
	private:                                         \
		FixtureImpl() : Fixture(NAME) {}             \
		static const Fixture& _self;                 \
	};                                               \
	const Fixture& FixtureImpl<NAME>::_self          \
		= Runner::get().add([]() -> auto&            \
		{ static FixtureImpl<NAME> f; return f; }())
