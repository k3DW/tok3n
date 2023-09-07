#include "pch.h"

using L = Literal<"literal">;

FIXTURE("Literal");

TEST("Literal", "Requirements")
{
	ASSERT_IS_PARSER(L, LiteralType, Output);
}

TEST("Literal", "Parse 'literal'")
{
	ASSERT_PARSE_SUCCESS(L, "literal", "literal", "");
	ASSERT_PARSE_SUCCESS(L, "literally", "literal", "ly");
	ASSERT_PARSE_FAILURE(L, "litera");
	ASSERT_PARSE_FAILURE(L, " literal");
	ASSERT_PARSE_FAILURE(L, "LITERAL");
	ASSERT_PARSE_FAILURE(L, "LITERALLY");
}



TEST("Literal", "Parse empty")
{
	ASSERT_BASIC_PARSER_CONSTRUCTIBLE(Literal, "");

	ASSERT_PARSE_SUCCESS(Literal<"">, "anything", "", "anything");
	ASSERT_PARSE_SUCCESS(Literal<"">, "", "", "");
}
