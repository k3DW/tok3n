// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("basic operators");

TEST("basic operators", "any<>")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
    EXPECT_THAT(parser_value<any<static_array(A, C)>>
                         .is<any1>);
    EXPECT_THAT(parser_value<any<static_array(B, D)>>
                         .is<any2>);
#else
    EXPECT_THAT(parser_value<any<static_array(A, B, C)>>
                         .is<any1>);
    EXPECT_THAT(parser_value<any<static_array(B, C, D)>>
                         .is<any2>);
#endif
    EXPECT_THAT(parser_value<any<static_array(X, Y, Z)>>
                         .is<any3>);
    EXPECT_THAT(parser_value<any<static_array(B, C)>>
                         .is<any4>);
    EXPECT_THAT(parser_value<any<static_array(Com)>>
                         .is<comma>);
    EXPECT_THAT(parser_value<any<static_array(Space, Dot)>>
                         .is<spacedot>);
    EXPECT_THAT(parser_value<any<(static_array<value_type, 0>{})>>
                         .is<any_of_parser<(static_array<value_type, 0>{})>{}>);
}

TEST("basic operators", "any_of<>")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
    EXPECT_THAT(parser_value<(any_of<A, C>)>
                         .is<any1>);
    EXPECT_THAT(parser_value<(any_of<B, D>)>
                         .is<any2>);
#else
    EXPECT_THAT(parser_value<(any_of<A, B, C>)>
                         .is<any1>);
    EXPECT_THAT(parser_value<(any_of<B, C, D>)>
                         .is<any2>);
#endif
    EXPECT_THAT(parser_value<(any_of<X, Y, Z>)>
                         .is<any3>);
    EXPECT_THAT(parser_value<(any_of<B, C>)>
                         .is<any4>);
    EXPECT_THAT(parser_value<(any_of<Com>)>
                         .is<comma>);
    EXPECT_THAT(parser_value<(any_of<Space, Dot>)>
                         .is<spacedot>);
}

TEST("basic operators", "none<>")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
    EXPECT_THAT(parser_value<none<static_array(A, C)>>
                         .is<none1>);
    EXPECT_THAT(parser_value<none<static_array(B, D)>>
                         .is<none2>);
#else
    EXPECT_THAT(parser_value<none<static_array(A, B, C)>>
                         .is<none1>);
    EXPECT_THAT(parser_value<none<static_array(B, C, D)>>
                         .is<none2>);
#endif
    EXPECT_THAT(parser_value<none<static_array(X, Y, Z)>>
                         .is<none3>);
    EXPECT_THAT(parser_value<none<static_array(B, C)>>
                         .is<none4>);
    EXPECT_THAT(parser_value<none<static_array(Z)>>
                         .is<none5>);
    EXPECT_THAT(parser_value<none<(static_array<value_type, 0>{})>>
                         .is<none_of_parser<(static_array<value_type, 0>{})>{}>);
}

TEST("basic operators", "none_of<>")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
    EXPECT_THAT(parser_value<(none_of<A, C>)>
                         .is<none1>);
    EXPECT_THAT(parser_value<(none_of<B, D>)>
                         .is<none2>);
#else
    EXPECT_THAT(parser_value<(none_of<A, B, C>)>
                         .is<none1>);
    EXPECT_THAT(parser_value<(none_of<B, C, D>)>
                         .is<none2>);
#endif
    EXPECT_THAT(parser_value<(none_of<X, Y, Z>)>
                         .is<none3>);
    EXPECT_THAT(parser_value<(none_of<B, C>)>
                         .is<none4>);
    EXPECT_THAT(parser_value<(none_of<Z>)>
                         .is<none5>);
}

TEST("basic operators", "all<>")
{
    EXPECT_THAT(parser_value<all<static_array(X, Y, Z)>>
                         .is<all1>);
    EXPECT_THAT(parser_value<all<static_array(Y, Z)>>
                         .is<all2>);
    EXPECT_THAT(parser_value<all<static_array(A, B)>>
                         .is<all3>);
    EXPECT_THAT(parser_value<all<static_array(Question, Question)>>
                         .is<qq>);
    EXPECT_THAT(parser_value<all<static_array(A, B, C)>>
                         .is<abc>);
    EXPECT_THAT(parser_value<all<(static_array<value_type, 0>{})>>
                         .is<all_of_parser<(static_array<value_type, 0>{})>{}>);
}

TEST("basic operators", "all_of<>")
{
    EXPECT_THAT(parser_value<(all_of<X, Y, Z>)>
                         .is<all1>);
    EXPECT_THAT(parser_value<(all_of<Y, Z>)>
                         .is<all2>);
    EXPECT_THAT(parser_value<(all_of<A, B>)>
                         .is<all3>);
    EXPECT_THAT(parser_value<(all_of<Question, Question>)>
                         .is<qq>);
    EXPECT_THAT(parser_value<(all_of<A, B, C>)>
                         .is<abc>);
}

TEST("basic operators", "ign<>")
{
    EXPECT_THAT(parser_value<ign<static_array(X, Y, Z)>>
                         .is<ignore_parser<All1>{}>);
    EXPECT_THAT(parser_value<ign<static_array(Y, Z)>>
                         .is<ignore_parser<All2>{}>);
    EXPECT_THAT(parser_value<ign<static_array(A, B)>>
                         .is<ignore_parser<All3>{}>);
    EXPECT_THAT(parser_value<ign<static_array(Question, Question)>>
                         .is<ignore_parser<QQ>{}>);
    EXPECT_THAT(parser_value<ign<static_array(A, B, C)>>
                         .is<ignore_parser<ABC>{}>);
    EXPECT_THAT(parser_value<ign<(static_array<value_type, 0>{})>>
                         .is<ignore_parser<all_of_parser<(static_array<value_type, 0>{})>>{}>);
}

TEST("basic operators", "Non sorted_and_uniqued")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)

// This discrepancy is because of the different implementations of `std::ranges::sort()`
#if defined(__clang__)
    EXPECT_THAT(parser_value<any<static_array(B, A, C, A, C, B, A, A, B, C, C, A)>>
                         .is<any_of_parser<static_array(A, C)>{}>);
    EXPECT_THAT(parser_value<none<static_array(B, A, C, A, C, B, A, A, B, C, C, A)>>
                         .is<none_of_parser<static_array(A, C)>{}>);
    EXPECT_THAT(parser_value<any<static_array(X, Y, Z, A, B, C)>>
                         .is<any_of_parser<static_array(B, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<none<static_array(X, Y, Z, A, B, C)>>
                         .is<none_of_parser<static_array(B, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<any<static_array(A, B, C, X, Y, Z)>>
                         .is<any_of_parser<static_array(B, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<none<static_array(A, B, C, X, Y, Z)>>
                         .is<none_of_parser<static_array(B, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<any<static_array(A, X, B, Y, C, Z)>>
                         .is<any_of_parser<static_array(B, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<none<static_array(A, X, B, Y, C, Z)>>
                         .is<none_of_parser<static_array(B, C, X, Y, Z)>{}>);
#elif defined(_MSC_VER) || defined(__GNUC__)
    EXPECT_THAT(parser_value<any<static_array(B, A, C, A, C, B, A, A, B, C, C, A)>>
                         .is<any_of_parser<static_array(B, C)>{}>);
    EXPECT_THAT(parser_value<none<static_array(B, A, C, A, C, B, A, A, B, C, C, A)>>
                         .is<none_of_parser<static_array(B, C)>{}>);
    EXPECT_THAT(parser_value<any<static_array(X, Y, Z, A, B, C)>>
                         .is<any_of_parser<static_array(A, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<none<static_array(X, Y, Z, A, B, C)>>
                         .is<none_of_parser<static_array(A, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<any<static_array(A, B, C, X, Y, Z)>>
                         .is<any_of_parser<static_array(A, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<none<static_array(A, B, C, X, Y, Z)>>
                         .is<none_of_parser<static_array(A, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<any<static_array(A, X, B, Y, C, Z)>>
                         .is<any_of_parser<static_array(A, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<none<static_array(A, X, B, Y, C, Z)>>
                         .is<none_of_parser<static_array(A, C, X, Y, Z)>{}>);
#else
#error
#endif

#else

    EXPECT_THAT(parser_value<any<static_array(B, A, C, A, C, B, A, A, B, C, C, A)>>
                         .is<any_of_parser<static_array(A, B, C)>{}>);
    EXPECT_THAT(parser_value<none<static_array(B, A, C, A, C, B, A, A, B, C, C, A)>>
                         .is<none_of_parser<static_array(A, B, C)>{}>);
    EXPECT_THAT(parser_value<any<static_array(X, Y, Z, A, B, C)>>
                         .is<any_of_parser<static_array(A, B, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<none<static_array(X, Y, Z, A, B, C)>>
                         .is<none_of_parser<static_array(A, B, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<any<static_array(A, B, C, X, Y, Z)>>
                         .is<any_of_parser<static_array(A, B, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<none<static_array(A, B, C, X, Y, Z)>>
                         .is<none_of_parser<static_array(A, B, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<any<static_array(A, X, B, Y, C, Z)>>
                         .is<any_of_parser<static_array(A, B, C, X, Y, Z)>{}>);
    EXPECT_THAT(parser_value<none<static_array(A, X, B, Y, C, Z)>>
                         .is<none_of_parser<static_array(A, B, C, X, Y, Z)>{}>);

#endif
}

} // namespace
} // namespace k3::tok3n::tests
