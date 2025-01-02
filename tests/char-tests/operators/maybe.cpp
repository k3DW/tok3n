// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("maybe operator");

TEST("maybe operator", "~maybe_parser")
{
	ASSERT_PARSER_VALUES_EQ(~may1, may1);
	ASSERT_PARSER_VALUES_EQ(~~may1, may1);
	ASSERT_PARSER_VALUES_EQ(~~~may1, may1);
	ASSERT_PARSER_VALUES_EQ(~may2, may2);
	ASSERT_PARSER_VALUES_EQ(~~may2, may2);
	ASSERT_PARSER_VALUES_EQ(~~~may2, may2);
	ASSERT_PARSER_VALUES_EQ(~may3, may3);
	ASSERT_PARSER_VALUES_EQ(~~may3, may3);
	ASSERT_PARSER_VALUES_EQ(~~~may3, may3);
	ASSERT_PARSER_VALUES_EQ(~may4, may4);
	ASSERT_PARSER_VALUES_EQ(~~may4, may4);
	ASSERT_PARSER_VALUES_EQ(~~~may4, may4);
}

TEST("maybe operator", "~one_or_more_parser")
{
	ASSERT_PARSER_VALUES_EQ(~oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~~oom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~~oom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~~oom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~oom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~oom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~~oom4, zom4);
}

TEST("maybe operator", "~zero_or_more_parser")
{
	ASSERT_PARSER_VALUES_EQ(~zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~~~zom1, zom1);
	ASSERT_PARSER_VALUES_EQ(~zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~~~zom2, zom2);
	ASSERT_PARSER_VALUES_EQ(~zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~~~zom3, zom3);
	ASSERT_PARSER_VALUES_EQ(~zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~zom4, zom4);
	ASSERT_PARSER_VALUES_EQ(~~~zom4, zom4);
}

TEST("maybe operator", "non consteval")
{
	(~any1).parse(TT("abc"));
}



#define MAYBE_OPERATOR_ASSERTER(P)                                                      \
	[]<parser PP>(PP) {                                                                 \
		DEP_ASSERT_UNARY_OPERABLE(~, PP{}, P{});                                        \
		if constexpr (PP::family == maybe_family)                                       \
		{                                                                               \
			DEP_ASSERT_PARSER_VALUES_EQ(~PP{}, PP{},                                    \
										~P{},  P{});                                    \
		}                                                                               \
		else if constexpr (PP::family == one_or_more_family)                            \
		{                                                                               \
			DEP_ASSERT_PARSER_VALUES_EQ(~PP{}, zero_or_more_parser<underlying_t<PP>>{}, \
										~P{},  zero_or_more_parser<underlying_t<P>>{}); \
		}                                                                               \
		else if constexpr (PP::family == zero_or_more_family)                           \
		{                                                                               \
			DEP_ASSERT_PARSER_VALUES_EQ(~PP{}, PP{},                                    \
										~P{},  P{});                                    \
		}                                                                               \
		else                                                                            \
		{                                                                               \
			DEP_ASSERT_PARSER_VALUES_EQ(~PP{}, maybe_parser<PP>{},                      \
										~P{},  maybe_parser<P>{});                      \
		}                                                                               \
	}(P{});

TEST("maybe operator", "~{anything}")
{
	ASSERT_ALL_SAMPLES(MAYBE_OPERATOR_ASSERTER);
}
