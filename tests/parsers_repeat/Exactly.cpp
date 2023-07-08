#include "pch.h"

TEST("Exactly", "Requirements")
{
	assert
		, IsParser<Exa1, ExactlyType, std::array<std::string_view, 3>>
		, IsParser<Exa2, ExactlyType, std::array<std::string_view, 5>>
		, IsParser<Exa3, ExactlyType, std::array<std::string_view, 4>>
		, IsParser<Exa4, ExactlyType, std::array<std::tuple<std::string_view, std::string_view>, 2>>
		;
}

TEST("Exactly", "Constructibility")
{
	using traits::repeat::Exactly::constructible;
	assert
		, not constructible::from<OC1, 0>
		, constructible::from<OC1, 1>
		, constructible::from<OC1, 2>
		;
}

TEST("Exactly", "Parse Exactly<Literal>")
{
	ASSERT_PARSE_FAILURE(Exa1, "litera");
	ASSERT_PARSE_FAILURE(Exa1, "literal");
	ASSERT_PARSE_FAILURE(Exa1, "literalliteral");
	ASSERT_PARSE_SUCCESS(Exa1, "literalliteralliteral", { "literal", "literal", "literal" }, "");
	ASSERT_PARSE_FAILURE(Exa1, " literalliteralliteral");
	ASSERT_PARSE_SUCCESS(Exa1, "literalliteralliteralliteral", { "literal", "literal", "literal" }, "literal");
	ASSERT_PARSE_SUCCESS(Exa1, "literalliteralliterallyliteral", { "literal", "literal", "literal" }, "lyliteral");
	ASSERT_PARSE_FAILURE(Exa1, "");
}
TEST("Exactly", "Parse Exactly<OneChar>")
{
	ASSERT_PARSE_SUCCESS(Exa2, "abcbaa", { "a", "b", "c", "b", "a" }, "a");
	ASSERT_PARSE_FAILURE(Exa2, "fedcba");
	ASSERT_PARSE_SUCCESS(Exa2, "cbabcccbjklmnop", { "c", "b", "a", "b", "c" }, "ccbjklmnop");
	ASSERT_PARSE_FAILURE(Exa2, "");
}
TEST("Exactly", "Parse Exactly<Choice>")
{
	ASSERT_PARSE_SUCCESS(Exa3, "abliteralcbliteralcf", { "a", "b", "literal", "c" }, "bliteralcf");
	ASSERT_PARSE_SUCCESS(Exa3, "abliteralcblitralcf", { "a", "b", "literal", "c" }, "blitralcf");
	ASSERT_PARSE_SUCCESS(Exa3, "literalabacliteral", { "literal", "a", "b", "a" }, "cliteral");
	ASSERT_PARSE_FAILURE(Exa3, "");
}
TEST("Exactly", "Parse Exactly<Sequence>")
{
	ASSERT_PARSE_SUCCESS(Exa4, "literalaliteralcliteralcliteralb", {{ {"literal", "a"}, {"literal", "c"} }}, "literalcliteralb");
	ASSERT_PARSE_SUCCESS(Exa4, "literalaliteralcliteralcliteralbliteral", {{ {"literal", "a"}, {"literal", "c"} }}, "literalcliteralbliteral");
	ASSERT_PARSE_FAILURE(Exa4, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Exa4, "");
}
