#include "pch.h"

TEST("OneOrMore", "Requirements")
{
	assert
		, IsParser<Oom1, OneOrMoreType, std::vector<std::string_view>>
		, IsParser<Oom2, OneOrMoreType, std::vector<std::string_view>>
		, IsParser<Oom3, OneOrMoreType, std::vector<std::string_view>>
		, IsParser<Oom4, OneOrMoreType, std::vector<std::tuple<std::string_view, std::string_view>>>
		;
}

TEST("OneOrMore", "Parse OneOrMore<Literal>")
{
	ASSERT_PARSE_FAILURE(Oom1, "litera");
	ASSERT_PARSE_SUCCESS(Oom1, "literal", { "literal" }, "");
	ASSERT_PARSE_SUCCESS(Oom1, "literally", { "literal" }, "ly");
	ASSERT_PARSE_SUCCESS(Oom1, "literallitera", { "literal" }, "litera");
	ASSERT_PARSE_SUCCESS(Oom1, "literalliterallitera", { "literal", "literal" }, "litera");
	ASSERT_PARSE_FAILURE(Oom1, " literalliterallitera");
	ASSERT_PARSE_FAILURE(Oom1, "");
}
TEST("OneOrMore", "Parse OneOrMore<OneChar>")
{
	ASSERT_PARSE_SUCCESS(Oom2, "abcdef", { "a", "b", "c" }, "def");
	ASSERT_PARSE_FAILURE(Oom2, "fedcba");
	ASSERT_PARSE_SUCCESS(Oom2, "cbabcccbjklmnop", { "c", "b", "a", "b", "c", "c", "c", "b" }, "jklmnop");
	ASSERT_PARSE_FAILURE(Oom2, "");
}
TEST("OneOrMore", "Parse OneOrMore<Choice>")
{
	ASSERT_PARSE_SUCCESS(Oom3, "abliteralcbliteralcf", { "a", "b", "literal", "c", "b", "literal", "c" }, "f");
	ASSERT_PARSE_SUCCESS(Oom3, "abliteralcblitralcf", { "a", "b", "literal", "c", "b" }, "litralcf");
	ASSERT_PARSE_SUCCESS(Oom3, "literalabacliteral", { "literal", "a", "b", "a", "c", "literal" }, "");
	ASSERT_PARSE_FAILURE(Oom3, "");
}
TEST("OneOrMore", "Parse OneOrMore<Sequence>")
{
	ASSERT_PARSE_SUCCESS(Oom4, "literalaliteralcliteralcliteralb", { {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }, "");
	ASSERT_PARSE_SUCCESS(Oom4, "literalaliteralcliteralcliteralbliteral", { {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }, "literal");
	ASSERT_PARSE_FAILURE(Oom4, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Oom4, "");
}
