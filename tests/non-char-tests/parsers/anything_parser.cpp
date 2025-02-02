// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("anything_parser");

TEST("anything_parser", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Ant1, value_type);

	ASSERT_IS_PARSER(Ant1, value_type, anything_family, output_span<value_type>);
}

TEST("anything_parser", "Parse")
{
	ASSERT_PARSE_SUCCESS(Ant1, e(A, B, C), e(A), e(B, C));
	ASSERT_PARSE_SUCCESS(Ant1, e(A, C, B), e(A), e(C, B));
	ASSERT_PARSE_SUCCESS(Ant1, e(B, A, C), e(B), e(A, C));
	ASSERT_PARSE_SUCCESS(Ant1, e(B, C, A), e(B), e(C, A));
	ASSERT_PARSE_SUCCESS(Ant1, e(C, A, B), e(C), e(A, B));
	ASSERT_PARSE_SUCCESS(Ant1, e(C, B, A), e(C), e(B, A));
	ASSERT_PARSE_SUCCESS(Ant1, e(X, Y, Z), e(X), e(Y, Z));
	ASSERT_PARSE_SUCCESS(Ant1, e(X, Z, Y), e(X), e(Z, Y));
	ASSERT_PARSE_SUCCESS(Ant1, e(Y, X, Z), e(Y), e(X, Z));
	ASSERT_PARSE_SUCCESS(Ant1, e(Y, Z, X), e(Y), e(Z, X));
	ASSERT_PARSE_SUCCESS(Ant1, e(Z, X, Y), e(Z), e(X, Y));
	ASSERT_PARSE_SUCCESS(Ant1, e(Z, Y, X), e(Z), e(Y, X));
	ASSERT_PARSE_FAILURE(Ant1, e());
}
