#include "pch.h"

using L = Literal<"literal">;

TEST("Literal", "Requirements")
{
	ASSERT_IS_PARSER(L, LiteralType, std::string_view);
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



using constructible = traits::basic::constructible<Literal>;

TEST("Literal", "Constructible from ascii only")
{
	ASSERT_PARSER_BASIC_CONSTRUCTIBLE(Literal, "literal");
	ASSERT_PARSER_BASIC_CONSTRUCTIBLE(Literal, "lïterål");
}

TEST("Literal", "Parse empty")
{
	ASSERT_PARSER_BASIC_CONSTRUCTIBLE(Literal, "");

	ASSERT_PARSE_SUCCESS(Literal<"">, "anything", "", "anything");
	ASSERT_PARSE_SUCCESS(Literal<"">, "", "", "");
}
