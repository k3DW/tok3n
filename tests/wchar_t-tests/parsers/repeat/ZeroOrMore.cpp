#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("ZeroOrMore");

TEST("ZeroOrMore", "Requirements")
{
	ASSERT_IS_PARSER(Zom1, ZeroOrMoreFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Zom2, ZeroOrMoreFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Zom3, ZeroOrMoreFamily, std::vector<Output<wchar_t>>);
	ASSERT_IS_PARSER(Zom4, ZeroOrMoreFamily, std::vector<std::tuple<Output<wchar_t>, Output<wchar_t>>>);
}

TEST("ZeroOrMore", "Parse ZeroOrMore<AllOf>")
{
	using vec_type = std::vector<Output<wchar_t>>;
	ASSERT_PARSE_SUCCESS(Zom1, L"litera", vec_type{}, L"litera");
	ASSERT_PARSE_SUCCESS(Zom1, L"literal", vec_type({ L"literal" }), L"");
	ASSERT_PARSE_SUCCESS(Zom1, L"literally", vec_type({ L"literal" }), L"ly");
	ASSERT_PARSE_SUCCESS(Zom1, L"literallitera", vec_type({ L"literal" }), L"litera");
	ASSERT_PARSE_SUCCESS(Zom1, L"literalliterallitera", vec_type({ L"literal", L"literal" }), L"litera");
	ASSERT_PARSE_SUCCESS(Zom1, L" literalliterallitera", vec_type{}, L" literalliterallitera");
	ASSERT_PARSE_SUCCESS(Zom1, L"", vec_type{}, L"");
}
TEST("ZeroOrMore", "Parse ZeroOrMore<AnyOf>")
{
	using vec_type = std::vector<Output<wchar_t>>;
	ASSERT_PARSE_SUCCESS(Zom2, L"abcdef", vec_type({ L"a", L"b", L"c" }), L"def");
	ASSERT_PARSE_SUCCESS(Zom2, L"fedcba", vec_type{}, L"fedcba");
	ASSERT_PARSE_SUCCESS(Zom2, L"cbabcccbjklmnop", vec_type({ L"c", L"b", L"a", L"b", L"c", L"c", L"c", L"b" }), L"jklmnop");
	ASSERT_PARSE_SUCCESS(Zom2, L"", vec_type{}, L"");
}
TEST("ZeroOrMore", "Parse ZeroOrMore<Choice>")
{
	using vec_type = std::vector<Output<wchar_t>>;
	ASSERT_PARSE_SUCCESS(Zom3, L"abliteralcbliteralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b", L"literal", L"c" }), L"f");
	ASSERT_PARSE_SUCCESS(Zom3, L"abliteralcblitralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b" }), L"litralcf");
	ASSERT_PARSE_SUCCESS(Zom3, L"literalabacliteral", vec_type({ L"literal", L"a", L"b", L"a", L"c", L"literal" }), L"");
	ASSERT_PARSE_SUCCESS(Zom3, L"", vec_type{}, L"");
}
TEST("ZeroOrMore", "Parse ZeroOrMore<Sequence>")
{
	using vec_type = std::vector<std::tuple<Output<wchar_t>, Output<wchar_t>>>;
	ASSERT_PARSE_SUCCESS(Zom4, L"literalaliteralcliteralcliteralb", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L"");
	ASSERT_PARSE_SUCCESS(Zom4, L"literalaliteralcliteralcliteralbliteral", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L"literal");
	ASSERT_PARSE_SUCCESS(Zom4, L"aliteralaliteralcliteralbliteral", vec_type{}, L"aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Zom4, L"", vec_type{}, L"");
}
