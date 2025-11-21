// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("anything_parser");

TEST("anything_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Ant1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Ant1> | has_family<anything_family>);

    EXPECT_THAT(the_parser<Ant1> | is_parser_for<value_type>.with_result<output_span<value_type>>);
}

TEST("anything_parser", "Parse")
{
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e(A, B, C), e(A), e(B, C)));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e(A, C, B), e(A), e(C, B)));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e(B, A, C), e(B), e(A, C)));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e(B, C, A), e(B), e(C, A)));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e(C, A, B), e(C), e(A, B)));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e(C, B, A), e(C), e(B, A)));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e(X, Y, Z), e(X), e(Y, Z)));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e(X, Z, Y), e(X), e(Z, Y)));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e(Y, X, Z), e(Y), e(X, Z)));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e(Y, Z, X), e(Y), e(Z, X)));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e(Z, X, Y), e(Z), e(X, Y)));
    EXPECT_THAT(the_parser<Ant1> | SUCCEEDS_PARSING(e(Z, Y, X), e(Z), e(Y, X)));
    EXPECT_THAT(the_parser<Ant1> | FAILS_PARSING(e()));
}

} // namespace
} // namespace k3::tok3n::tests
