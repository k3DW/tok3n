// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

using Single = any_of_parser<static_array(A)>;
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
using Multi  = any_of_parser<static_array(A, C)>;
#else
using Multi  = any_of_parser<static_array(A, B, C)>;
#endif

FIXTURE("any_of_parser");

TEST("any_of_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Single> | has_family<any_of_family>);
    EXPECT_THAT(the_parser<Multi> | has_family<any_of_family>);

    EXPECT_THAT(the_parser<Single> | is_parser_for<value_type>.with_result<output_span<value_type>>);
    EXPECT_THAT(the_parser<Multi> | is_parser_for<value_type>.with_result<output_span<value_type>>);
}

TEST("any_of_parser", "Parse single")
{
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e(A, B), e(A), e(B)));
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e(B, A), e(B), e(A)));
#else
    ASSERT_PARSE_FAILURE(Single, e(B, A));
#endif
    EXPECT_THAT(the_parser<Single> | SUCCEEDS_PARSING(e(A, B, C), e(A), e(B, C)));
    ASSERT_PARSE_FAILURE(Single, e(Space, A));
}

TEST("any_of_parser", "Parse multi")
{
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e(A, B, C), e(A), e(B, C)));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e(A, C, B), e(A), e(C, B)));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e(B, A, C), e(B), e(A, C)));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e(B, C, A), e(B), e(C, A)));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e(C, A, B), e(C), e(A, B)));
    EXPECT_THAT(the_parser<Multi> | SUCCEEDS_PARSING(e(C, B, A), e(C), e(B, A)));
    ASSERT_PARSE_FAILURE(Multi, e(X, Y, Z));
    ASSERT_PARSE_FAILURE(Multi, e(X, Z, Y));
    ASSERT_PARSE_FAILURE(Multi, e(Y, X, Z));
    ASSERT_PARSE_FAILURE(Multi, e(Y, Z, X));
    ASSERT_PARSE_FAILURE(Multi, e(Z, X, Y));
    ASSERT_PARSE_FAILURE(Multi, e(Z, Y, X));
}



TEST("any_of_parser", "Constructible from lexicographically sorted only")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_valid_with<static_array(A, C)>);
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<static_array(C, A)>);
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<static_array(A, B)>);
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<static_array(A, B, C)>);
#else
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_valid_with<static_array(A, B, C)>);
#endif
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<static_array(A, C, B)>);
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<static_array(B, A, C)>);
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<static_array(B, C, A)>);
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<static_array(C, A, B)>);
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_not_valid_with<static_array(C, B, A)>);
}

TEST("any_of_parser", "Parse")
{
    EXPECT_THAT(the_basic_parser_family<any_of_parser>.is_valid_with<L"">);

    ASSERT_PARSE_FAILURE(any_of_parser<(static_array<value_type, 0>{})>, e(A, B, C));
    ASSERT_PARSE_FAILURE(any_of_parser<(static_array<value_type, 0>{})>, e());
}

} // namespace
} // namespace k3::tok3n::tests
