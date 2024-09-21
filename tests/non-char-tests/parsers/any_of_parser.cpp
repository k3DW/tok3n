#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

using Single = any_of_parser<static_array(A)>;
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
using Multi  = any_of_parser<static_array(A, C)>;
#else
using Multi  = any_of_parser<static_array(A, B, C)>;
#endif

FIXTURE("any_of_parser");

TEST("any_of_parser", "Requirements")
{
	ASSERT_IS_PARSER(Single, value_type, any_of_family, output_span<value_type>);
	ASSERT_IS_PARSER(Multi, value_type, any_of_family, output_span<value_type>);
}

TEST("any_of_parser", "Parse single")
{
	ASSERT_PARSE_SUCCESS(Single, e(A, B), e(A), e(B));
#if defined(VALUE_TYPE_STRUCTURAL_OP_EQUALS)
	ASSERT_PARSE_SUCCESS(Single, e(B, A), e(B), e(A));
#else
	ASSERT_PARSE_FAILURE(Single, e(B, A));
#endif
	ASSERT_PARSE_SUCCESS(Single, e(A, B, C), e(A), e(B, C));
	ASSERT_PARSE_FAILURE(Single, e(Space, A));
}

TEST("any_of_parser", "Parse multi")
{
	ASSERT_PARSE_SUCCESS(Multi, e(A, B, C), e(A), e(B, C));
	ASSERT_PARSE_SUCCESS(Multi, e(A, C, B), e(A), e(C, B));
	ASSERT_PARSE_SUCCESS(Multi, e(B, A, C), e(B), e(A, C));
	ASSERT_PARSE_SUCCESS(Multi, e(B, C, A), e(B), e(C, A));
	ASSERT_PARSE_SUCCESS(Multi, e(C, A, B), e(C), e(A, B));
	ASSERT_PARSE_SUCCESS(Multi, e(C, B, A), e(C), e(B, A));
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
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(any_of_parser, static_array(A, C));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, static_array(C, A));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, static_array(A, B));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, static_array(A, B, C));
#else
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(any_of_parser, static_array(A, B, C));
#endif
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, static_array(A, C, B));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, static_array(B, A, C));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, static_array(B, C, A));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, static_array(C, A, B));
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(any_of_parser, static_array(C, B, A));
}

TEST("any_of_parser", "Parse")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(any_of_parser, L"");
	
	ASSERT_PARSE_FAILURE(any_of_parser<(static_array<value_type, 0>{})>, e(A, B, C));
	ASSERT_PARSE_FAILURE(any_of_parser<(static_array<value_type, 0>{})>, e());
}
