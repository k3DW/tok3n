#include "pch.h"
#include "char-samples/char-samples.h"

using Single = AnyOf<'a'>;
using Multi  = AnyOf<"abc">;

FIXTURE("AnyOf");

TEST("AnyOf", "Requirements")
{
	ASSERT_IS_PARSER(Single, AnyOfFamily, Output<char>);
	ASSERT_IS_PARSER(Multi, AnyOfFamily, Output<char>);
}

TEST("AnyOf", "Parse single char")
{
	ASSERT_PARSE_SUCCESS(Single, "ab", "a", "b");
	ASSERT_PARSE_FAILURE(Single, "ba");
	ASSERT_PARSE_SUCCESS(Single, "abc", "a", "bc");
	ASSERT_PARSE_FAILURE(Single, "Ab");
	ASSERT_PARSE_FAILURE(Single, "Abc");
	ASSERT_PARSE_FAILURE(Single, " abc");
}

TEST("AnyOf", "Parse multi char")
{
	ASSERT_PARSE_SUCCESS(Multi, "abc", "a", "bc");
	ASSERT_PARSE_SUCCESS(Multi, "acb", "a", "cb");
	ASSERT_PARSE_SUCCESS(Multi, "bac", "b", "ac");
	ASSERT_PARSE_SUCCESS(Multi, "bca", "b", "ca");
	ASSERT_PARSE_SUCCESS(Multi, "cab", "c", "ab");
	ASSERT_PARSE_SUCCESS(Multi, "cba", "c", "ba");
	ASSERT_PARSE_FAILURE(Multi, "ABC");
	ASSERT_PARSE_FAILURE(Multi, "ACB");
	ASSERT_PARSE_FAILURE(Multi, "BAC");
	ASSERT_PARSE_FAILURE(Multi, "BCA");
	ASSERT_PARSE_FAILURE(Multi, "CAB");
	ASSERT_PARSE_FAILURE(Multi, "CBA");
	ASSERT_PARSE_FAILURE(Multi, "dcba");
	ASSERT_PARSE_FAILURE(Multi, " cba");
}



TEST("AnyOf", "Constructible from lexicographically sorted only")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(AnyOf, "abc");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, "acb");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, "bac");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, "bca");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, "cab");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(AnyOf, "cba");
}

TEST("AnyOf", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(AnyOf, "");
	
	ASSERT_PARSE_FAILURE(AnyOf<"">, "anything");
	ASSERT_PARSE_FAILURE(AnyOf<"">, "");
}
