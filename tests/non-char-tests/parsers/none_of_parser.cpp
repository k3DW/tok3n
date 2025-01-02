// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

using Single = none_of_parser<static_array(A)>;
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
using Multi  = none_of_parser<static_array(A, C)>;
#else
using Multi  = none_of_parser<static_array(A, B, C)>;
#endif

FIXTURE("none_of_parser");

TEST("none_of_parser", "Requirements")
{
	ASSERT_IS_PARSER(Single, value_type, none_of_family, output_span<value_type>);
	ASSERT_IS_PARSER(Multi, value_type, none_of_family, output_span<value_type>);
}

TEST("none_of_parser", "Parse single")
{
	ASSERT_PARSE_FAILURE(Single, e(A, B));
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
	ASSERT_PARSE_FAILURE(Single, e(B, A));
#else
	ASSERT_PARSE_SUCCESS(Single, e(B, A), e(B), e(A));
#endif
	ASSERT_PARSE_FAILURE(Single, e(A, B, C));
	ASSERT_PARSE_SUCCESS(Single, e(Space, A), e(Space), e(A));
}

TEST("none_of_parser", "Parse multi")
{
	ASSERT_PARSE_FAILURE(Multi, e(A, B, C));
	ASSERT_PARSE_FAILURE(Multi, e(A, C, B));
	ASSERT_PARSE_FAILURE(Multi, e(B, A, C));
	ASSERT_PARSE_FAILURE(Multi, e(B, C, A));
	ASSERT_PARSE_FAILURE(Multi, e(C, A, B));
	ASSERT_PARSE_FAILURE(Multi, e(C, B, A));
	ASSERT_PARSE_SUCCESS(Multi, e(X, Y, Z), e(X), e(Y, Z));
	ASSERT_PARSE_SUCCESS(Multi, e(X, Z, Y), e(X), e(Z, Y));
	ASSERT_PARSE_SUCCESS(Multi, e(Y, X, Z), e(Y), e(X, Z));
	ASSERT_PARSE_SUCCESS(Multi, e(Y, Z, X), e(Y), e(Z, X));
	ASSERT_PARSE_SUCCESS(Multi, e(Z, X, Y), e(Z), e(X, Y));
	ASSERT_PARSE_SUCCESS(Multi, e(Z, Y, X), e(Z), e(Y, X));
}



TEST("none_of_parser", "Constructible from lexicographically sorted only")
{
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(none_of_parser, static_array(A, C));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, static_array(C, A));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, static_array(A, B));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, static_array(A, B, C));
#else
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(none_of_parser, static_array(A, B, C));
#endif
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, static_array(A, C, B));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, static_array(B, A, C));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, static_array(B, C, A));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, static_array(C, A, B));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(none_of_parser, static_array(C, B, A));
}

TEST("none_of_parser", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(none_of_parser, L"");

	ASSERT_PARSE_SUCCESS(none_of_parser<(static_array<value_type, 0>{})>, e(A, B, C), e(A), e(B, C));
	ASSERT_PARSE_FAILURE(none_of_parser<(static_array<value_type, 0>{})>, e());
}
