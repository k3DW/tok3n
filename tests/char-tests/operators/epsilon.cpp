// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("epsilon operator");

namespace {

template <auto lhs, auto rhs>
concept choice_operable = requires { lhs | rhs; };

} // namespace

TEST("epsilon operator", ".of<>")
{
    EXPECT_THAT(parser_value<eps.of<value_type>>
                         .is<epsilon_parser<value_type>{}>);
}

TEST("epsilon operator", "P | eps")
{
    EXPECT_THAT(parser_value<any1 | eps>
                         .is<(choice_parser<Any1, epsilon_parser<value_type>>{})>);
    EXPECT_THAT(parser_value<any2 | eps>
                         .is<(choice_parser<Any2, epsilon_parser<value_type>>{})>);
    EXPECT_THAT(parser_value<any3 | eps>
                         .is<(choice_parser<Any3, epsilon_parser<value_type>>{})>);
}

TEST("epsilon operator", "eps | P")
{
    ASSERT((not choice_operable<eps, any1>)) << "The expression `eps | any1` compiled, but it should not";
    ASSERT((not choice_operable<eps, any2>)) << "The expression `eps | any2` compiled, but it should not";
    ASSERT((not choice_operable<eps, any3>)) << "The expression `eps | any3` compiled, but it should not";
}



#define EPSILON_OPERATOR_ASSERTER(P)                                                      \
    []<parser PP>(PP) {                                                                   \
        ASSERT_COMPILE_TIME((requires { { PP{} | eps } -> k3::tok3n::detail::parser; })); \
        ASSERT_COMPILE_TIME((not requires { eps | PP{}; }));                              \
        EXPECT_THAT(parser_value<PP{} | eps>                                              \
                             .is<PP{} | epsilon_parser<::value_type>{}>);                 \
    }(P{});

TEST("epsilon operator", "eps anything")
{
    ASSERT_ALL_SAMPLES(EPSILON_OPERATOR_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
