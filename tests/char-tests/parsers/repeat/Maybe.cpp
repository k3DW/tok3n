#include "pch.h"

FIXTURE("Maybe");

TEST("Maybe", "Requirements")
{
	ASSERT_IS_PARSER(May1, MaybeFamily, std::optional<Output<char>>);
	ASSERT_IS_PARSER(May2, MaybeFamily, std::optional<Output<char>>);
	ASSERT_IS_PARSER(May3, MaybeFamily, std::optional<Output<char>>);
	ASSERT_IS_PARSER(May4, MaybeFamily, std::optional<std::tuple<Output<char>, Output<char>>>);
}

TEST("Maybe", "Parse Maybe<AllOf>")
{
	ASSERT_PARSE_SUCCESS(May1, "litera", std::nullopt, "litera");
	ASSERT_PARSE_SUCCESS(May1, "literal", std::optional("literal"), "");
	ASSERT_PARSE_SUCCESS(May1, "literally", std::optional("literal"), "ly");
	ASSERT_PARSE_SUCCESS(May1, "literallitera", std::optional("literal"), "litera");
	ASSERT_PARSE_SUCCESS(May1, "literalliterallitera", std::optional("literal"), "literallitera");
	ASSERT_PARSE_SUCCESS(May1, " literalliterallitera", std::nullopt, " literalliterallitera");
	ASSERT_PARSE_SUCCESS(May1, "", std::nullopt, "");
}
TEST("Maybe", "Parse Maybe<AnyOf>")
{
	ASSERT_PARSE_SUCCESS(May2, "abcdef", std::optional("a"), "bcdef");
	ASSERT_PARSE_SUCCESS(May2, "fedcba", std::nullopt, "fedcba");
	ASSERT_PARSE_SUCCESS(May2, "cbabcccbjklmnop", std::optional("c"), "babcccbjklmnop");
	ASSERT_PARSE_SUCCESS(May2, "", std::nullopt, "");
}
TEST("Maybe", "Parse Maybe<Choice>")
{
	ASSERT_PARSE_SUCCESS(May3, "abliteralcbliteralcf", std::optional("a"), "bliteralcbliteralcf");
	ASSERT_PARSE_SUCCESS(May3, "abliteralcblitralcf", std::optional("a"), "bliteralcblitralcf");
	ASSERT_PARSE_SUCCESS(May3, "literalabacliteral", std::optional("literal"), "abacliteral");
	ASSERT_PARSE_SUCCESS(May3, "", std::nullopt, "");
}
TEST("Maybe", "Parse Maybe<Sequence>")
{
	ASSERT_PARSE_SUCCESS(May4, "literalaliteralcliteralcliteralb", std::optional(std::tuple("literal", "a")), "literalcliteralcliteralb");
	ASSERT_PARSE_SUCCESS(May4, "literalaliteralcliteralcliteralbliteral", std::optional(std::tuple("literal", "a")), "literalcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(May4, "aliteralaliteralcliteralbliteral", std::nullopt, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(May4, "", std::nullopt, "");
}
