// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

using L = all_of_parser<detail::static_array(X, Y, Z)>;

FIXTURE("all_of_parser");

TEST("all_of_parser", "Requirements")
{
    EXPECT_THAT(the_parser<L> | has_family<all_of_family>);
    EXPECT_THAT(the_parser<L> | is_parser_for<value_type>.with_result<output_span<value_type>>);
}

TEST("all_of_parser", "Parse")
{
    EXPECT_THAT(the_parser<L> | SUCCEEDS_PARSING(e(X, Y, Z), e(X, Y, Z), e()));
    EXPECT_THAT(the_parser<L> | SUCCEEDS_PARSING(e(X, Y, Z, A, B), e(X, Y, Z), e(A, B)));
    ASSERT_PARSE_FAILURE(L, e(X, Y));
    ASSERT_PARSE_FAILURE(L, e(Space, X, Y));
}



TEST("all_of_parser", "Parse empty")
{
    EXPECT_THAT(the_basic_parser_family<all_of_parser>.is_valid_with<e()>);

    EXPECT_THAT(the_parser<all_of_parser<(static_array<value_type, 0>{})>> | SUCCEEDS_PARSING(e(A, B, C), e(), e(A, B, C)));
    EXPECT_THAT(the_parser<all_of_parser<(static_array<value_type, 0>{})>> | SUCCEEDS_PARSING(e(), e(), e()));
}

} // namespace
} // namespace k3::tok3n::tests
