#pragma once
#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <k3/tok3n/types/StaticArray.h>

class Test;

class Fixture
{
public:
	void add_test(Test& test);

	std::string_view name() const
	{
		return _name;
	}

	int run(std::ostream& os, std::optional<std::string_view> test_name = std::nullopt);

	void print_brief(std::ostream& os) const;
	void print_errors(std::ostream& os) const;
	std::size_t count_failures() const;

	void list(std::ostream& os) const;

protected:
	Fixture(std::string name)
		: _name(std::move(name))
	{}

	virtual ~Fixture() {}

private:
	std::string _name;
	std::unordered_map<std::string_view, Test*> _tests;
};



template <k3::tok3n::StaticArray name>
requires std::same_as<char, typename decltype(name)::value_type>
class FixtureImpl {};

#define FIXTURE_(NAME)                               \
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

#define FIXTURE(NAME) FIXTURE_(ASSEMBLY " " NAME)
