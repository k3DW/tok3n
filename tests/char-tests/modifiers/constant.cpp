// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("constant modifier");

TEST("constant modifier", "prefix")
{
    EXPECT_THAT(parser_value<con1>
                         .is<constant<1>(+abc)>);
    EXPECT_THAT(parser_value<con2>
                         .is<constant<'t'>(~(abc | qq))>);
    EXPECT_THAT(parser_value<con3>
                         .is<constant<true>(abc >> *qq)>);
    EXPECT_THAT(parser_value<con4>
                         .is<constant<nullptr>(+abc >> ~(abc | qq))>);
}

TEST("constant modifier", "infix")
{
    EXPECT_THAT(parser_value<con1>
                         .is<+abc % constant<1>>);
    EXPECT_THAT(parser_value<con2>
                         .is<~(abc | qq) % constant<'t'>>);
    EXPECT_THAT(parser_value<con3>
                         .is<(abc >> *qq) % constant<true>>);
    EXPECT_THAT(parser_value<con4>
                         .is<(+abc >> ~(abc | qq)) % constant<nullptr>>);
}

TEST("constant modifier", "non consteval")
{
    (constant<0>(any1)).parse(TT("abc"));
    (any1 % constant<0>).parse(TT("abc"));
}



#define CONSTANT_MODIFIER_ASSERTER(P)                                              \
    {                                                                              \
        using R = constant_parser<P, integral_constant<0>>;                        \
        EXPECT_THAT(the_parser<P> | is_modifiable_by<constant<0>>.with_result<R>); \
    }

TEST("constant modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(CONSTANT_MODIFIER_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
