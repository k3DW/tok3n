// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("epsilon_parser");

TEST("epsilon_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Eps1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Eps1> | has_family<epsilon_family>);

    EXPECT_THAT(the_parser<Eps1> | is_parser_for<value_type>.with_result<void>);
}

TEST("epsilon_parser", "Parse")
{
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(A, B, C), e(A, B, C)));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(A, C, B), e(A, C, B)));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(B, A, C), e(B, A, C)));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(B, C, A), e(B, C, A)));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(C, A, B), e(C, A, B)));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(C, B, A), e(C, B, A)));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(X, Y, Z), e(X, Y, Z)));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(X, Z, Y), e(X, Z, Y)));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(Y, X, Z), e(Y, X, Z)));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(Y, Z, X), e(Y, Z, X)));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(Z, X, Y), e(Z, X, Y)));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(Z, Y, X), e(Z, Y, X)));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e(), e()));
}

} // namespace
} // namespace k3::tok3n::tests
