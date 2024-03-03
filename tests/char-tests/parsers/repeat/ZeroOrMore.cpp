#include "pch.h"

FIXTURE("ZeroOrMore");

TEST("ZeroOrMore", "Requirements")
{
	ASSERT_IS_PARSER(Zom1, ZeroOrMoreFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Zom2, ZeroOrMoreFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Zom3, ZeroOrMoreFamily, std::vector<Output<char>>);
	ASSERT_IS_PARSER(Zom4, ZeroOrMoreFamily, std::vector<std::tuple<Output<char>, Output<char>>>);
}

TEST("ZeroOrMore", "Parse ZeroOrMore<AllOf>")
{
	using vec_type = std::vector<Output<char>>;
	ASSERT_PARSE_SUCCESS(Zom1, "litera", vec_type{}, "litera");
	ASSERT_PARSE_SUCCESS(Zom1, "literal", vec_type({ "literal" }), "");
	ASSERT_PARSE_SUCCESS(Zom1, "literally", vec_type({ "literal" }), "ly");
	ASSERT_PARSE_SUCCESS(Zom1, "literallitera", vec_type({ "literal" }), "litera");
	ASSERT_PARSE_SUCCESS(Zom1, "literalliterallitera", vec_type({ "literal", "literal" }), "litera");
	ASSERT_PARSE_SUCCESS(Zom1, " literalliterallitera", vec_type{}, " literalliterallitera");
	ASSERT_PARSE_SUCCESS(Zom1, "", vec_type{}, "");
}
TEST("ZeroOrMore", "Parse ZeroOrMore<AnyOf>")
{
	using vec_type = std::vector<Output<char>>;
	ASSERT_PARSE_SUCCESS(Zom2, "abcdef", vec_type({ "a", "b", "c" }), "def");
	ASSERT_PARSE_SUCCESS(Zom2, "fedcba", vec_type{}, "fedcba");
	ASSERT_PARSE_SUCCESS(Zom2, "cbabcccbjklmnop", vec_type({ "c", "b", "a", "b", "c", "c", "c", "b" }), "jklmnop");
	ASSERT_PARSE_SUCCESS(Zom2, "", vec_type{}, "");
}
TEST("ZeroOrMore", "Parse ZeroOrMore<Choice>")
{
	using vec_type = std::vector<Output<char>>;
	ASSERT_PARSE_SUCCESS(Zom3, "abliteralcbliteralcf", vec_type({ "a", "b", "literal", "c", "b", "literal", "c" }), "f");
	ASSERT_PARSE_SUCCESS(Zom3, "abliteralcblitralcf", vec_type({ "a", "b", "literal", "c", "b" }), "litralcf");
	ASSERT_PARSE_SUCCESS(Zom3, "literalabacliteral", vec_type({ "literal", "a", "b", "a", "c", "literal" }), "");
	ASSERT_PARSE_SUCCESS(Zom3, "", vec_type{}, "");
}
TEST("ZeroOrMore", "Parse ZeroOrMore<Sequence>")
{
	using vec_type = std::vector<std::tuple<Output<char>, Output<char>>>;
	ASSERT_PARSE_SUCCESS(Zom4, "literalaliteralcliteralcliteralb", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), "");
	ASSERT_PARSE_SUCCESS(Zom4, "literalaliteralcliteralcliteralbliteral", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), "literal");
	ASSERT_PARSE_SUCCESS(Zom4, "aliteralaliteralcliteralbliteral", vec_type{}, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Zom4, "", vec_type{}, "");
}
