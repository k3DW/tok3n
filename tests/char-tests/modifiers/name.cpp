// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("name modifier");

TEST("name modifier", "prefix")
{
    EXPECT_THAT(parser_value<nam1>
                         .is<name<"nam1">(abc)>);
    EXPECT_THAT(parser_value<nam2>
                         .is<name<"nam2">(+abc)>);
    EXPECT_THAT(parser_value<nam3>
                         .is<name<"nam3">(~(abc | qq))>);
    EXPECT_THAT(parser_value<nam4>
                         .is<name<"nam4">(abc >> *qq)>);
}

TEST("name modifier", "infix")
{
    EXPECT_THAT(parser_value<nam1>
                         .is<abc % name<"nam1">>);
    EXPECT_THAT(parser_value<nam2>
                         .is<+abc % name<"nam2">>);
    EXPECT_THAT(parser_value<nam3>
                         .is<~(abc | qq) % name<"nam3">>);
    EXPECT_THAT(parser_value<nam4>
                         .is<(abc >> *qq) % name<"nam4">>);
}

TEST("name modifier", "non consteval")
{
    (name<"test">(any1)).parse(TT("abc"));
    (any1 % name<"test">).parse(TT("abc"));
}



#define NAME_MODIFIER_CALLABLE_ASSERTER(P)                                          \
    ASSERT_MODIFIER_CALLABLE_R(name<"test1">, (P{}), (named_parser<P, "test1">{})); \
    ASSERT_MODIFIER_CALLABLE_R(name<"test2">, (P{}), (named_parser<P, "test2">{}));

#define NAME_MODIFIER_OPERABLE_ASSERTER(P)                                               \
    ASSERT_MODIFIER_MODULO_OPERABLE_R(P{}, name<"test1">, (named_parser<P, "test1">{})); \
    ASSERT_MODIFIER_MODULO_OPERABLE_R(P{}, name<"test2">, (named_parser<P, "test2">{}));

TEST("name modifier", "modify callable anything")
{
    ASSERT_ALL_SAMPLES(NAME_MODIFIER_CALLABLE_ASSERTER);
}

TEST("name modifier", "modify operable anything")
{
    ASSERT_ALL_SAMPLES(NAME_MODIFIER_OPERABLE_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
