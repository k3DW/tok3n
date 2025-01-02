// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_FRAMEWORK_FIXTURE_HPP
#define K3_TOK3N_TESTS_FRAMEWORK_FIXTURE_HPP

#include <iosfwd>
#include <string>
#include <string_view>
#include <unordered_map>
#include "framework/Hash.hpp"
#include "framework/Test.hpp"

struct FixtureResult;

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

#endif // K3_TOK3N_TESTS_FRAMEWORK_FIXTURE_HPP
