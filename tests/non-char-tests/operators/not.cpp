// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("not operator");

TEST("not operator", "!any_of_parser")
{
    EXPECT_THAT(parser_value<!any1>
                         .is<none1>);
    EXPECT_THAT(parser_value<!any2>
                         .is<none2>);
    EXPECT_THAT(parser_value<!any3>
                         .is<none3>);
    EXPECT_THAT(parser_value<!!any1>
                         .is<any1>);
    EXPECT_THAT(parser_value<!!any2>
                         .is<any2>);
    EXPECT_THAT(parser_value<!!any3>
                         .is<any3>);
}

TEST("not operator", "!none_of_parser")
{
    EXPECT_THAT(parser_value<!none1>
                         .is<any1>);
    EXPECT_THAT(parser_value<!none2>
                         .is<any2>);
    EXPECT_THAT(parser_value<!none3>
                         .is<any3>);
    EXPECT_THAT(parser_value<!!none1>
                         .is<none1>);
    EXPECT_THAT(parser_value<!!none2>
                         .is<none2>);
    EXPECT_THAT(parser_value<!!none3>
                         .is<none3>);
}



#define NOT_OPERATOR_ASSERTER(P)                                           \
    []<parser PP>(PP) {                                                    \
        if constexpr (PP::family == any_of_family)                         \
        {                                                                  \
            ASSERT_COMPILE_TIME(                                           \
                (requires { { !PP{} }-> k3::tok3n::detail::parser; }));    \
            EXPECT_THAT(parser_value<!PP{}>                                \
                    .DEP_TEMPLATE is<none_of_parser<underlying_v<PP>>{}>); \
        }                                                                  \
        else if constexpr (PP::family == none_of_family)                   \
        {                                                                  \
            ASSERT_COMPILE_TIME(                                           \
                (requires { { !PP{} }-> k3::tok3n::detail::parser; }));    \
            EXPECT_THAT(parser_value<!PP{}>                                \
                    .DEP_TEMPLATE is<any_of_parser<underlying_v<PP>>{}>);  \
        }                                                                  \
        else                                                               \
        {                                                                  \
            ASSERT_COMPILE_TIME((not requires { !PP{}; }));                \
        }                                                                  \
    }(P{});

TEST("not operator", "!{anything}")
{
    ASSERT_ALL_SAMPLES(NOT_OPERATOR_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
