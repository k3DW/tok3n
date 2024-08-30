#pragma once
#include <iosfwd>
#include <string>
#include <string_view>
#include <unordered_map>
#include "framework/Hash.h"

struct FixtureResult;
class Test;

class Fixture
{
public:
	void add_test(Test&& test);

	std::string_view name() const
	{
		return _name;
	}

	FixtureResult run(std::ostream& os) const;
	FixtureResult run(std::ostream& os, std::string_view test_name) const;

	void list(std::ostream& os) const;

protected:
	Fixture(std::string name)
		: _name(std::move(name))
	{}

	virtual ~Fixture() {}

private:
	std::string _name;
	std::unordered_map<std::string_view, Test> _tests;
};



template <std::size_t hash>
class FixtureImpl {};

#define FIXTURE(NAME)                                           \
	template <>                                                 \
	class FixtureImpl<test_hash(NAME)> : private Fixture        \
	{                                                           \
	private:                                                    \
		FixtureImpl() : Fixture(NAME) {}                        \
		static const Fixture& _self;                            \
	};                                                          \
	const Fixture& FixtureImpl<test_hash(NAME)>::_self          \
		= Runner::get().add([]() -> auto&                       \
		{ static FixtureImpl<test_hash(NAME)> f; return f; }())
