// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("name modifier");

TEST("name modifier", "prefix")
{
	ASSERT_PARSER_VALUES_EQ(nam1, name<"nam1">(abc));
	ASSERT_PARSER_VALUES_EQ(nam2, name<"nam2">(+abc));
	ASSERT_PARSER_VALUES_EQ(nam3, name<"nam3">(~(abc | qq)));
	ASSERT_PARSER_VALUES_EQ(nam4, name<"nam4">(abc >> *qq));
}

TEST("name modifier", "infix")
{
	ASSERT_PARSER_VALUES_EQ(nam1, abc % name<"nam1">);
	ASSERT_PARSER_VALUES_EQ(nam2, +abc % name<"nam2">);
	ASSERT_PARSER_VALUES_EQ(nam3, ~(abc | qq) % name<"nam3">);
	ASSERT_PARSER_VALUES_EQ(nam4, (abc >> *qq) % name<"nam4">);
}

TEST("name modifier", "non consteval")
{
	(name<"test">(any1)).parse(TT("abc"));
	(any1 % name<"test">).parse(TT("abc"));
}



#define NAME_MODIFIER_ASSERTER(P)                                                 \
    ASSERT_MODIFIER_CALLABLE_R(name<"test1">, (P{}), (named_parser<P, "test1">{}));      \
    ASSERT_MODIFIER_CALLABLE_R(name<"test2">, (P{}), (named_parser<P, "test2">{}));      \
	ASSERT_MODIFIER_MODULO_OPERABLE_R(P{}, name<"test1">, (named_parser<P, "test1">{})); \
	ASSERT_MODIFIER_MODULO_OPERABLE_R(P{}, name<"test2">, (named_parser<P, "test2">{}));

TEST("name modifier", "modify anything")
{
	ASSERT_ALL_SAMPLES(NAME_MODIFIER_ASSERTER);
}
