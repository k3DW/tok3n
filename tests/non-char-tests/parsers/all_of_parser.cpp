// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

using L = all_of_parser<static_array(X, Y, Z)>;

FIXTURE("all_of_parser");

TEST("all_of_parser", "Requirements")
{
	ASSERT_IS_PARSER(L, value_type, all_of_family, output_span<value_type>);
}

TEST("all_of_parser", "Parse")
{
	ASSERT_PARSE_SUCCESS(L, e(X, Y, Z), e(X, Y, Z), e());
	ASSERT_PARSE_SUCCESS(L, e(X, Y, Z, A, B), e(X, Y, Z), e(A, B));
	ASSERT_PARSE_FAILURE(L, e(X, Y));
	ASSERT_PARSE_FAILURE(L, e(Space, X, Y));
}



TEST("all_of_parser", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(all_of_parser, e());

	ASSERT_PARSE_SUCCESS(all_of_parser<(static_array<value_type, 0>{})>, e(A, B, C), e(), e(A, B, C));
	ASSERT_PARSE_SUCCESS(all_of_parser<(static_array<value_type, 0>{})>, e(), e(), e());
}
