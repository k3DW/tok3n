#include "pch.h"

using L = AllOf<"literal">;

FIXTURE("AllOf");

TEST("AllOf", "Requirements")
{
	ASSERT_IS_PARSER(L, AllOfType, Output<char>);
}

TEST("AllOf", "Parse 'literal'")
{
	ASSERT_PARSE_SUCCESS(L, "literal", "literal", "");
	ASSERT_PARSE_SUCCESS(L, "literally", "literal", "ly");
	ASSERT_PARSE_FAILURE(L, "litera");
	ASSERT_PARSE_FAILURE(L, " literal");
	ASSERT_PARSE_FAILURE(L, "LITERAL");
	ASSERT_PARSE_FAILURE(L, "LITERALLY");
}



TEST("AllOf", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(AllOf, "");

	ASSERT_PARSE_SUCCESS(AllOf<"">, "anything", "", "anything");
	ASSERT_PARSE_SUCCESS(AllOf<"">, "", "", "");
}
