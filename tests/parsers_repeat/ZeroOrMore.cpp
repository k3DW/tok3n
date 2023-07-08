#include "pch.h"

TEST("ZeroOrMore", "Requirements")
{
	assert
		, IsParser<Zom1, ZeroOrMoreType, std::vector<std::string_view>>
		, IsParser<Zom2, ZeroOrMoreType, std::vector<std::string_view>>
		, IsParser<Zom3, ZeroOrMoreType, std::vector<std::string_view>>
		, IsParser<Zom4, ZeroOrMoreType, std::vector<std::tuple<std::string_view, std::string_view>>>
		;
}

TEST("ZeroOrMore", "Parse ZeroOrMore<Literal>")
{
	ASSERT_PARSE_SUCCESS(Zom1, "litera", {}, "litera");
	ASSERT_PARSE_SUCCESS(Zom1, "literal", { "literal" }, "");
	ASSERT_PARSE_SUCCESS(Zom1, "literally", { "literal" }, "ly");
	ASSERT_PARSE_SUCCESS(Zom1, "literallitera", { "literal" }, "litera");
	ASSERT_PARSE_SUCCESS(Zom1, "literalliterallitera", { "literal", "literal" }, "litera");
	ASSERT_PARSE_SUCCESS(Zom1, " literalliterallitera", {}, " literalliterallitera");
	ASSERT_PARSE_SUCCESS(Zom1, "", {}, "");
}
TEST("ZeroOrMore", "Parse ZeroOrMore<OneChar>")
{
	ASSERT_PARSE_SUCCESS(Zom2, "abcdef", { "a", "b", "c" }, "def");
	ASSERT_PARSE_SUCCESS(Zom2, "fedcba", {}, "fedcba");
	ASSERT_PARSE_SUCCESS(Zom2, "cbabcccbjklmnop", { "c", "b", "a", "b", "c", "c", "c", "b" }, "jklmnop");
	ASSERT_PARSE_SUCCESS(Zom2, "", {}, "");
}
TEST("ZeroOrMore", "Parse ZeroOrMore<Choice>")
{
	ASSERT_PARSE_SUCCESS(Zom3, "abliteralcbliteralcf", { "a", "b", "literal", "c", "b", "literal", "c" }, "f");
	ASSERT_PARSE_SUCCESS(Zom3, "abliteralcblitralcf", { "a", "b", "literal", "c", "b" }, "litralcf");
	ASSERT_PARSE_SUCCESS(Zom3, "literalabacliteral", { "literal", "a", "b", "a", "c", "literal" }, "");
	ASSERT_PARSE_SUCCESS(Zom3, "", {}, "");
}
TEST("ZeroOrMore", "Parse ZeroOrMore<Sequence>")
{
	ASSERT_PARSE_SUCCESS(Zom4, "literalaliteralcliteralcliteralb", { {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }, "");
	ASSERT_PARSE_SUCCESS(Zom4, "literalaliteralcliteralcliteralbliteral", { {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }, "literal");
	ASSERT_PARSE_SUCCESS(Zom4, "aliteralaliteralcliteralbliteral", {}, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Zom4, "", {}, "");
}
