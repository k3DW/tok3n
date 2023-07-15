#include "pch.h"

TEST("Exactly", "Requirements")
{
	ASSERT_IS_PARSER(Exa1, ExactlyType, std::array<std::string_view, 3>);
	ASSERT_IS_PARSER(Exa2, ExactlyType, std::array<std::string_view, 5>);
	ASSERT_IS_PARSER(Exa3, ExactlyType, std::array<std::string_view, 4>);
	ASSERT_IS_PARSER(Exa4, ExactlyType, std::array<std::tuple<std::string_view, std::string_view>, 2>);
}

TEST("Exactly", "Constructibility")
{
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Exactly, OC1, Index<0>);
	ASSERT_PARSER_CONSTRUCTIBLE(Exactly, OC1, Index<1>);
	ASSERT_PARSER_CONSTRUCTIBLE(Exactly, OC1, Index<2>);

	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Exactly, OC1, Const<0>);
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Exactly, OC1, Const<1>);
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Exactly, OC1, Const<2>);
}

TEST("Exactly", "Parse Exactly<Literal>")
{
	using array_type = std::array<std::string_view, 3>;
	ASSERT_PARSE_FAILURE(Exa1, "litera");
	ASSERT_PARSE_FAILURE(Exa1, "literal");
	ASSERT_PARSE_FAILURE(Exa1, "literalliteral");
	ASSERT_PARSE_SUCCESS(Exa1, "literalliteralliteral", array_type({ "literal", "literal", "literal" }), "");
	ASSERT_PARSE_FAILURE(Exa1, " literalliteralliteral");
	ASSERT_PARSE_SUCCESS(Exa1, "literalliteralliteralliteral", array_type({ "literal", "literal", "literal" }), "literal");
	ASSERT_PARSE_SUCCESS(Exa1, "literalliteralliterallyliteral", array_type({ "literal", "literal", "literal" }), "lyliteral");
	ASSERT_PARSE_FAILURE(Exa1, "");
}
TEST("Exactly", "Parse Exactly<OneChar>")
{
	using array_type = std::array<std::string_view, 5>;
	ASSERT_PARSE_SUCCESS(Exa2, "abcbaa", array_type({ "a", "b", "c", "b", "a" }), "a");
	ASSERT_PARSE_FAILURE(Exa2, "fedcba");
	ASSERT_PARSE_SUCCESS(Exa2, "cbabcccbjklmnop", array_type({ "c", "b", "a", "b", "c" }), "ccbjklmnop");
	ASSERT_PARSE_FAILURE(Exa2, "");
}
TEST("Exactly", "Parse Exactly<Choice>")
{
	using array_type = std::array<std::string_view, 4>;
	ASSERT_PARSE_SUCCESS(Exa3, "abliteralcbliteralcf", array_type({ "a", "b", "literal", "c" }), "bliteralcf");
	ASSERT_PARSE_SUCCESS(Exa3, "abliteralcblitralcf", array_type({ "a", "b", "literal", "c" }), "blitralcf");
	ASSERT_PARSE_SUCCESS(Exa3, "literalabacliteral", array_type({ "literal", "a", "b", "a" }), "cliteral");
	ASSERT_PARSE_FAILURE(Exa3, "");
}
TEST("Exactly", "Parse Exactly<Sequence>")
{
	using array_type = std::array<std::tuple<std::string_view, std::string_view>, 2>;
	ASSERT_PARSE_SUCCESS(Exa4, "literalaliteralcliteralcliteralb", array_type({ {"literal", "a"}, {"literal", "c"} }), "literalcliteralb");
	ASSERT_PARSE_SUCCESS(Exa4, "literalaliteralcliteralcliteralbliteral", array_type({ {"literal", "a"}, {"literal", "c"} }), "literalcliteralbliteral");
	ASSERT_PARSE_FAILURE(Exa4, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Exa4, "");
}
