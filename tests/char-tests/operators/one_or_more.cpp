// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("one_or_more operator");

TEST("one_or_more operator", "+maybe_parser")
{
	ASSERT_PARSER_VALUES_EQ(+may1, zom1);
	ASSERT_PARSER_VALUES_EQ(+ +may1, zom1);
	ASSERT_PARSER_VALUES_EQ(+ + +may1, zom1);
	ASSERT_PARSER_VALUES_EQ(+may2, zom2);
	ASSERT_PARSER_VALUES_EQ(+ +may2, zom2);
	ASSERT_PARSER_VALUES_EQ(+ + +may2, zom2);
	ASSERT_PARSER_VALUES_EQ(+may3, zom3);
	ASSERT_PARSER_VALUES_EQ(+ +may3, zom3);
	ASSERT_PARSER_VALUES_EQ(+ + +may3, zom3);
	ASSERT_PARSER_VALUES_EQ(+may4, zom4);
	ASSERT_PARSER_VALUES_EQ(+ +may4, zom4);
	ASSERT_PARSER_VALUES_EQ(+ + +may4, zom4);
}

TEST("one_or_more operator", "+one_or_more_parser")
{
	ASSERT_PARSER_VALUES_EQ(+oom1, oom1);
	ASSERT_PARSER_VALUES_EQ(+ +oom1, oom1);
	ASSERT_PARSER_VALUES_EQ(+ + +oom1, oom1);
	ASSERT_PARSER_VALUES_EQ(+oom2, oom2);
	ASSERT_PARSER_VALUES_EQ(+ +oom2, oom2);
	ASSERT_PARSER_VALUES_EQ(+ + +oom2, oom2);
	ASSERT_PARSER_VALUES_EQ(+oom3, oom3);
	ASSERT_PARSER_VALUES_EQ(+ +oom3, oom3);
	ASSERT_PARSER_VALUES_EQ(+ + +oom3, oom3);
	ASSERT_PARSER_VALUES_EQ(+oom4, oom4);
	ASSERT_PARSER_VALUES_EQ(+ +oom4, oom4);
	ASSERT_PARSER_VALUES_EQ(+ + +oom4, oom4);
}

TEST("one_or_more operator", "+zero_or_more_parser")
{
	ASSERT_PARSER_VALUES_EQ(+zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(+ +zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(+ + +zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(+zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(+ +zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(+ + +zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(+zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(+ +zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(+ + +zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(+zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(+ +zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(+ + +zom4, zom4);
}

TEST("one_or_more operator", "non consteval")
{
	(+any1).parse(TT("abc"));
}



#define ONE_OR_MORE_OPERATOR_ASSERTER(P)                                                \
	[]<parser PP>(PP) {                                                                 \
		DEP_ASSERT_UNARY_OPERABLE(+, PP{}, P{});                                        \
		if constexpr (PP::family == maybe_family)                                       \
		{                                                                               \
			DEP_ASSERT_PARSER_VALUES_EQ(+PP{}, zero_or_more_parser<underlying_t<PP>>{}, \
										+P{},  zero_or_more_parser<underlying_t<P>>{}); \
		}                                                                               \
		else if constexpr (PP::family == one_or_more_family)                            \
		{                                                                               \
			DEP_ASSERT_PARSER_VALUES_EQ(+PP{}, PP{},                                    \
										+P{},  P{});                                    \
		}                                                                               \
		else if constexpr (PP::family == zero_or_more_family)                           \
		{                                                                               \
			DEP_ASSERT_PARSER_VALUES_EQ(+PP{}, PP{},                                    \
										+P{},  P{});                                    \
		}                                                                               \
		else                                                                            \
		{                                                                               \
			DEP_ASSERT_PARSER_VALUES_EQ(+PP{}, one_or_more_parser<PP>{},                \
										+P{},  one_or_more_parser<P>{});                \
		}                                                                               \
	}(P{});

TEST("one_or_more operator", "+{anything}")
{
	ASSERT_ALL_SAMPLES(ONE_OR_MORE_OPERATOR_ASSERTER);
}
