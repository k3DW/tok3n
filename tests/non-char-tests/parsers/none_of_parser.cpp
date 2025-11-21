// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

using Single = none_of_parser<static_array(A)>;
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
using Multi  = none_of_parser<static_array(A, C)>;
#else
using Multi  = none_of_parser<static_array(A, B, C)>;
#endif

FIXTURE("none_of_parser");

TEST("none_of_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Single> | has_family<none_of_family>);
    EXPECT_THAT(the_parser<Multi> | has_family<none_of_family>);

    EXPECT_THAT(the_parser<Single> | is_parser_for<value_type>.with_result<output_span<value_type>>);
    EXPECT_THAT(the_parser<Multi> | is_parser_for<value_type>.with_result<output_span<value_type>>);
}

TEST("none_of_parser", "Parse single")
{
    ASSERT_PARSE_FAILURE(Single, e(A, B));
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
    ASSERT_PARSE_FAILURE(Single, e(B, A));
#else
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e(B, A), e(B), e(A)));
#endif
    ASSERT_PARSE_FAILURE(Single, e(A, B, C));
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e(Space, A), e(Space), e(A)));
}

TEST("none_of_parser", "Parse multi")
{
    ASSERT_PARSE_FAILURE(Multi, e(A, B, C));
    ASSERT_PARSE_FAILURE(Multi, e(A, C, B));
    ASSERT_PARSE_FAILURE(Multi, e(B, A, C));
    ASSERT_PARSE_FAILURE(Multi, e(B, C, A));
    ASSERT_PARSE_FAILURE(Multi, e(C, A, B));
    ASSERT_PARSE_FAILURE(Multi, e(C, B, A));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e(X, Y, Z), e(X), e(Y, Z)));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e(X, Z, Y), e(X), e(Z, Y)));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e(Y, X, Z), e(Y), e(X, Z)));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e(Y, Z, X), e(Y), e(Z, X)));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e(Z, X, Y), e(Z), e(X, Y)));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e(Z, Y, X), e(Z), e(Y, X)));
}



TEST("none_of_parser", "Constructible from lexicographically sorted only")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_valid_with<static_array(A, C)>);
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<static_array(C, A)>);
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<static_array(A, B)>);
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<static_array(A, B, C)>);
#else
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_valid_with<static_array(A, B, C)>);
#endif
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<static_array(A, C, B)>);
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<static_array(B, A, C)>);
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<static_array(B, C, A)>);
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<static_array(C, A, B)>);
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_not_valid_with<static_array(C, B, A)>);
}

TEST("none_of_parser", "Parse empty")
{
    EXPECT_THAT(the_basic_parser_family<none_of_parser>.is_valid_with<L"">);

    EXPECT_THAT(the_parser<none_of_parser<(static_array<value_type, 0>{})>> | SUCCEEDS_PARSING(e(A, B, C), e(A), e(B, C)));
    ASSERT_PARSE_FAILURE(none_of_parser<(static_array<value_type, 0>{})>, e());
}

} // namespace
} // namespace k3::tok3n::tests
