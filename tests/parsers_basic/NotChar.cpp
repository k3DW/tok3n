#include "pch.h"

using Single = NotChar<'a'>;
using Multi  = NotChar<"abc">;

FIXTURE("NotChar");

TEST("NotChar", "Requirements")
{
	ASSERT_IS_PARSER(Single, NotCharType, Output<char>);
	ASSERT_IS_PARSER(Multi, NotCharType, Output<char>);
}

TEST("NotChar", "Parse single char")
{
	ASSERT_PARSE_FAILURE(Single, "ab");
	ASSERT_PARSE_SUCCESS(Single, "ba", "b", "a");
	ASSERT_PARSE_FAILURE(Single, "abc");
	ASSERT_PARSE_SUCCESS(Single, "Ab", "A", "b");
	ASSERT_PARSE_SUCCESS(Single, "Abc", "A", "bc");
	ASSERT_PARSE_SUCCESS(Single, " abc", " ", "abc");
}

TEST("NotChar", "Parse multi char")
{
	ASSERT_PARSE_FAILURE(Multi, "abc");
	ASSERT_PARSE_FAILURE(Multi, "acb");
	ASSERT_PARSE_FAILURE(Multi, "bac");
	ASSERT_PARSE_FAILURE(Multi, "bca");
	ASSERT_PARSE_FAILURE(Multi, "cab");
	ASSERT_PARSE_FAILURE(Multi, "cba");
	ASSERT_PARSE_SUCCESS(Multi, "ABC", "A", "BC");
	ASSERT_PARSE_SUCCESS(Multi, "ACB", "A", "CB");
	ASSERT_PARSE_SUCCESS(Multi, "BAC", "B", "AC");
	ASSERT_PARSE_SUCCESS(Multi, "BCA", "B", "CA");
	ASSERT_PARSE_SUCCESS(Multi, "CAB", "C", "AB");
	ASSERT_PARSE_SUCCESS(Multi, "CBA", "C", "BA");
	ASSERT_PARSE_SUCCESS(Multi, "dcba", "d", "cba");
	ASSERT_PARSE_SUCCESS(Multi, "edcba", "e", "dcba");
	ASSERT_PARSE_SUCCESS(Multi, " cba", " ", "cba");
}



TEST("NotChar", "Constructible from lexicographically sorted only")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(NotChar, "abc");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NotChar, "acb");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NotChar, "bac");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NotChar, "bca");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NotChar, "cab");
	ASSERT_BASIC_PARSER_NOT_CONSTRUCTIBLE(NotChar, "cba");
}

TEST("NotChar", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(NotChar, "");

	ASSERT_PARSE_SUCCESS(NotChar<"">, "anything", "a", "nything");
	ASSERT_PARSE_FAILURE(NotChar<"">, "");
}
