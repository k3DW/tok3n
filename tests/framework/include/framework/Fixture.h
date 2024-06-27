#pragma once
#include <iosfwd>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include "framework/Hash.h"

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



template <std::size_t hash>
class FixtureImpl {};

#define FIXTURE_(NAME)                                          \
	template <>                                                 \
	class FixtureImpl<test_hash(NAME)> : public Fixture         \
	{                                                           \
	private:                                                    \
		FixtureImpl() : Fixture(NAME) {}                        \
		static const Fixture& _self;                            \
	};                                                          \
	const Fixture& FixtureImpl<test_hash(NAME)>::_self          \
		= Runner::get().add([]() -> auto&                       \
		{ static FixtureImpl<test_hash(NAME)> f; return f; }())

#define FIXTURE(NAME) FIXTURE_(NAME)
