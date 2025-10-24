// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("join modifier");

TEST("join modifier", "prefix")
{
    EXPECT_THAT(parser_value<joi1>
                         .is<join(abc)>);
    EXPECT_THAT(parser_value<abc>
                     .is_not<join(abc)>);
    EXPECT_THAT(parser_value<joi2>
                         .is<join(+abc)>);
    EXPECT_THAT(parser_value<joi3>
                         .is<join(~(abc | qq))>);
    EXPECT_THAT(parser_value<joi4>
                         .is<join(abc >> *qq)>);
    EXPECT_THAT(parser_value<joi5>
                         .is<join(+abc >> ~(abc | qq))>);
}

TEST("join modifier", "infix")
{
    EXPECT_THAT(parser_value<joi1>
                         .is<abc % join>);
    EXPECT_THAT(parser_value<abc>
                     .is_not<abc % join>);
    EXPECT_THAT(parser_value<joi2>
                         .is<+abc % join>);
    EXPECT_THAT(parser_value<joi3>
                         .is<~(abc | qq) % join>);
    EXPECT_THAT(parser_value<joi4>
                         .is<(abc >> *qq) % join>);
    EXPECT_THAT(parser_value<joi5>
                         .is<(+abc >> ~(abc | qq)) % join>);
}

TEST("join modifier", "idempotent")
{
    EXPECT_THAT(parser_value<joi1>
                         .is<join(joi1)>);
    EXPECT_THAT(parser_value<joi2>
                         .is<join(joi2)>);
    EXPECT_THAT(parser_value<joi3>
                         .is<join(joi3)>);
    EXPECT_THAT(parser_value<joi4>
                         .is<join(joi4)>);
    EXPECT_THAT(parser_value<joi5>
                         .is<join(joi5)>);
    EXPECT_THAT(parser_value<joi1>
                         .is<joi1 % join>);
    EXPECT_THAT(parser_value<joi2>
                         .is<joi2 % join>);
    EXPECT_THAT(parser_value<joi3>
                         .is<joi3 % join>);
    EXPECT_THAT(parser_value<joi4>
                         .is<joi4 % join>);
    EXPECT_THAT(parser_value<joi5>
                         .is<joi5 % join>);
}

TEST("join modifier", "non consteval")
{
    (join(any1)).parse(TT("abc"));
    (any1 % join).parse(TT("abc"));
}



#define JOIN_MODIFIER_ASSERTER(P)                                                \
    []<parser PP>(PP) {                                                          \
        if constexpr (PP::family == join_family)                                 \
        {                                                                        \
            DEP_ASSERT_MODIFIER_CALLABLE_R(join, (PP{}), PP{},                   \
                                           join, (P{}),  P{});                   \
            DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, join, PP{},              \
                                                  P{},  join, P{});              \
        }                                                                        \
        else                                                                     \
        {                                                                        \
            DEP_ASSERT_MODIFIER_CALLABLE_R(join, (PP{}), join_parser<PP>{},      \
                                           join, (P{}),  join_parser<P>{});      \
            DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, join, join_parser<PP>{}, \
                                                  P{},  join, join_parser<P>{}); \
        }                                                                        \
    }(P{});

TEST("join modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(JOIN_MODIFIER_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
