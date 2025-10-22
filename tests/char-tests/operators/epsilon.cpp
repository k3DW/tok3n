// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("epsilon operator");

namespace {

template <auto lhs, auto rhs>
concept choice_operable = requires { lhs | rhs; };

} // namespace

TEST("epsilon operator", ".of<>")
{
    ASSERT_PARSER_VALUES_EQ(eps.of<value_type>, epsilon_parser<value_type>{});
}

TEST("epsilon operator", "P | eps")
{
    ASSERT_PARSER_VALUES_EQ(any1 | eps, (choice_parser<Any1, epsilon_parser<value_type>>{}));
    ASSERT_PARSER_VALUES_EQ(any2 | eps, (choice_parser<Any2, epsilon_parser<value_type>>{}));
    ASSERT_PARSER_VALUES_EQ(any3 | eps, (choice_parser<Any3, epsilon_parser<value_type>>{}));
}

TEST("epsilon operator", "eps | P")
{
    ASSERT((not choice_operable<eps, any1>)) << "The expression `eps | any1` compiled, but it should not";
    ASSERT((not choice_operable<eps, any2>)) << "The expression `eps | any2` compiled, but it should not";
    ASSERT((not choice_operable<eps, any3>)) << "The expression `eps | any3` compiled, but it should not";
}



#define EPSILON_OPERATOR_ASSERTER(P)                                                    \
    []<parser PP>(PP) {                                                                 \
        DEP_ASSERT_BINARY_OPERABLE(|, PP{}, eps,                                        \
                                      P{},  eps);                                       \
        DEP_ASSERT_BINARY_NOT_OPERABLE(|, eps, PP{},                                    \
                                          eps, P{});                                    \
        DEP_ASSERT_PARSER_VALUES_EQ(PP{} | eps, PP{} | epsilon_parser<::value_type>{},  \
                                    P{}  | eps, P{}  | epsilon_parser<::value_type>{}); \
    }(P{});

TEST("epsilon operator", "eps anything")
{
    ASSERT_ALL_SAMPLES(EPSILON_OPERATOR_ASSERTER);
}
