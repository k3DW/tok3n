// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <k3/tok3n.hpp>
#include <cassert>

struct CharWrapper
{
	constexpr CharWrapper(char chr) : chr(chr) {}

	char chr;
};

template <auto value>
concept True = true;

template <CharWrapper wrapper>
requires True<wrapper>
struct Checker
{
	static constexpr bool check(char c)
	{
		return wrapper.chr == c;
	}
};

int main()
{
	{
		constexpr Checker<'a'> checker;

		constexpr bool compile_time = checker.check('a');
		bool run_time = checker.check('a');

		assert(compile_time); // Passes
		assert(run_time);     // Passes
	}

	[] {
		constexpr Checker<'b'> checker;

		constexpr bool compile_time = checker.check('b');
		bool run_time = checker.check('b');

		assert(compile_time); // Passes
		assert(run_time);     // Fails!! This is wrong
	}();
}

#if 0
#include <iostream>

int main()
{
	using namespace k3;
	using namespace k3::tok3n;

	constexpr auto oc = OneChar<"ab">{};
	constexpr auto test = exactly<2>(oc);

	auto result_ = test.parse("cbac");
	auto result_2 = test.parse("abac");
}
#endif
