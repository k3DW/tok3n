#include "pch.h"
#include "char-samples/char-samples.h"

FIXTURE("Exactly");

TEST("Exactly", "Requirements")
{
	ASSERT_IS_PARSER(Exa1, ExactlyFamily, std::array<Output<char>, 3>);
	ASSERT_IS_PARSER(Exa2, ExactlyFamily, std::array<Output<char>, 5>);
	ASSERT_IS_PARSER(Exa3, ExactlyFamily, std::array<Output<char>, 4>);
	ASSERT_IS_PARSER(Exa4, ExactlyFamily, std::array<std::tuple<Output<char>, Output<char>>, 2>);
}

TEST("Exactly", "Constructibility")
{
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Exactly, Any1, Index<0>);
	ASSERT_PARSER_CONSTRUCTIBLE(Exactly, Any1, Index<1>);
	ASSERT_PARSER_CONSTRUCTIBLE(Exactly, Any1, Index<2>);

	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Exactly, Any1, Const<0>);
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Exactly, Any1, Const<1>);
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Exactly, Any1, Const<2>);
}

TEST("Exactly", "Parse Exactly<AllOf>")
{
	using array_type = std::array<Output<char>, 3>;
	ASSERT_PARSE_FAILURE(Exa1, "litera");
	ASSERT_PARSE_FAILURE(Exa1, "literal");
	ASSERT_PARSE_FAILURE(Exa1, "literalliteral");
	ASSERT_PARSE_SUCCESS(Exa1, "literalliteralliteral", array_type({ "literal", "literal", "literal" }), "");
	ASSERT_PARSE_FAILURE(Exa1, " literalliteralliteral");
	ASSERT_PARSE_SUCCESS(Exa1, "literalliteralliteralliteral", array_type({ "literal", "literal", "literal" }), "literal");
	ASSERT_PARSE_SUCCESS(Exa1, "literalliteralliterallyliteral", array_type({ "literal", "literal", "literal" }), "lyliteral");
	ASSERT_PARSE_FAILURE(Exa1, "");
}
TEST("Exactly", "Parse Exactly<AnyOf>")
{
	using array_type = std::array<Output<char>, 5>;
	ASSERT_PARSE_SUCCESS(Exa2, "abcbaa", array_type({ "a", "b", "c", "b", "a" }), "a");
	ASSERT_PARSE_FAILURE(Exa2, "fedcba");
	ASSERT_PARSE_SUCCESS(Exa2, "cbabcccbjklmnop", array_type({ "c", "b", "a", "b", "c" }), "ccbjklmnop");
	ASSERT_PARSE_FAILURE(Exa2, "");
}
TEST("Exactly", "Parse Exactly<Choice>")
{
	using array_type = std::array<Output<char>, 4>;
	ASSERT_PARSE_SUCCESS(Exa3, "abliteralcbliteralcf", array_type({ "a", "b", "literal", "c" }), "bliteralcf");
	ASSERT_PARSE_SUCCESS(Exa3, "abliteralcblitralcf", array_type({ "a", "b", "literal", "c" }), "blitralcf");
	ASSERT_PARSE_SUCCESS(Exa3, "literalabacliteral", array_type({ "literal", "a", "b", "a" }), "cliteral");
	ASSERT_PARSE_FAILURE(Exa3, "");
}
TEST("Exactly", "Parse Exactly<Sequence>")
{
	using array_type = std::array<std::tuple<Output<char>, Output<char>>, 2>;
	ASSERT_PARSE_SUCCESS(Exa4, "literalaliteralcliteralcliteralb", array_type({ {"literal", "a"}, {"literal", "c"} }), "literalcliteralb");
	ASSERT_PARSE_SUCCESS(Exa4, "literalaliteralcliteralcliteralbliteral", array_type({ {"literal", "a"}, {"literal", "c"} }), "literalcliteralbliteral");
	ASSERT_PARSE_FAILURE(Exa4, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Exa4, "");
}
