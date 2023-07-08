#include "pch.h"

TEST("Maybe", "Requirements")
{
	assert
		, IsParser<May1, MaybeType, std::optional<std::string_view>>
		, IsParser<May2, MaybeType, std::optional<std::string_view>>
		, IsParser<May3, MaybeType, std::optional<std::string_view>>
		, IsParser<May4, MaybeType, std::optional<std::tuple<std::string_view, std::string_view>>>
		;
}

TEST("Maybe", "Parse Maybe<Literal>")
{
	ASSERT_PARSE_SUCCESS(May1, "litera", {}, "litera");
	ASSERT_PARSE_SUCCESS(May1, "literal", { "literal" }, "");
	ASSERT_PARSE_SUCCESS(May1, "literally", { "literal" }, "ly");
	ASSERT_PARSE_SUCCESS(May1, "literallitera", { "literal" }, "litera");
	ASSERT_PARSE_SUCCESS(May1, "literalliterallitera", { "literal" }, "literallitera");
	ASSERT_PARSE_SUCCESS(May1, " literalliterallitera", {}, " literalliterallitera");
	ASSERT_PARSE_SUCCESS(May1, "", {}, "");
}
TEST("Maybe", "Parse Maybe<OneChar>")
{
	ASSERT_PARSE_SUCCESS(May2, "abcdef", { "a" }, "bcdef");
	ASSERT_PARSE_SUCCESS(May2, "fedcba", {}, "fedcba");
	ASSERT_PARSE_SUCCESS(May2, "cbabcccbjklmnop", { "c" }, "babcccbjklmnop");
	ASSERT_PARSE_SUCCESS(May2, "", {}, "");
}
TEST("Maybe", "Parse Maybe<Choice>")
{
	ASSERT_PARSE_SUCCESS(May3, "abliteralcbliteralcf", { "a" }, "bliteralcbliteralcf");
	ASSERT_PARSE_SUCCESS(May3, "abliteralcblitralcf", { "a" }, "bliteralcblitralcf");
	ASSERT_PARSE_SUCCESS(May3, "literalabacliteral", { "literal" }, "abacliteral");
	ASSERT_PARSE_SUCCESS(May3, "", {}, "");
}
TEST("Maybe", "Parse Maybe<Sequence>")
{
	ASSERT_PARSE_SUCCESS(May4, "literalaliteralcliteralcliteralb", { {"literal", "a"} }, "literalcliteralcliteralb");
	ASSERT_PARSE_SUCCESS(May4, "literalaliteralcliteralcliteralbliteral", { {"literal", "a"} }, "literalcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(May4, "aliteralaliteralcliteralbliteral", {}, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(May4, "", {}, "");
}
