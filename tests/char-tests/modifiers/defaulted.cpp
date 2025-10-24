// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("defaulted modifier");

TEST("defaulted modifier", "prefix")
{
    EXPECT_THAT(parser_value<def1>
                         .is<defaulted<int>(+abc)>);
    EXPECT_THAT(parser_value<def2>
                         .is<defaulted<Class3>(~(abc | qq))>);
}

TEST("defaulted modifier", "infix")
{
    EXPECT_THAT(parser_value<def1>
                         .is<+abc % defaulted<int>>);
    EXPECT_THAT(parser_value<def2>
                         .is<~(abc | qq) % defaulted<Class3>>);
}

TEST("defaulted modifier", "non consteval")
{
    (defaulted<int>(any1)).parse(TT("abc"));
    (any1 % defaulted<int>).parse(TT("abc"));
}



#define DEFAULTED_MODIFIER_ASSERTER(P)                                                      \
    ASSERT_MODIFIER_CALLABLE_R(defaulted<bool>, (P{}), (defaulted_parser<P, bool>{}));      \
    ASSERT_MODIFIER_MODULO_OPERABLE_R(P{}, defaulted<bool>, (defaulted_parser<P, bool>{}));

TEST("defaulted modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(DEFAULTED_MODIFIER_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
