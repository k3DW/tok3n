#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("Exactly");

TEST("Exactly", "Requirements")
{
	ASSERT_IS_PARSER(Exa1, ExactlyFamily, std::array<Output<wchar_t>, 3>);
	ASSERT_IS_PARSER(Exa2, ExactlyFamily, std::array<Output<wchar_t>, 5>);
	ASSERT_IS_PARSER(Exa3, ExactlyFamily, std::array<Output<wchar_t>, 4>);
	ASSERT_IS_PARSER(Exa4, ExactlyFamily, std::array<std::tuple<Output<wchar_t>, Output<wchar_t>>, 2>);
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
	using array_type = std::array<Output<wchar_t>, 3>;
	ASSERT_PARSE_FAILURE(Exa1, L"litera");
	ASSERT_PARSE_FAILURE(Exa1, L"literal");
	ASSERT_PARSE_FAILURE(Exa1, L"literalliteral");
	ASSERT_PARSE_SUCCESS(Exa1, L"literalliteralliteral", array_type({ L"literal", L"literal", L"literal" }), L"");
	ASSERT_PARSE_FAILURE(Exa1, L" literalliteralliteral");
	ASSERT_PARSE_SUCCESS(Exa1, L"literalliteralliteralliteral", array_type({ L"literal", L"literal", L"literal" }), L"literal");
	ASSERT_PARSE_SUCCESS(Exa1, L"literalliteralliterallyliteral", array_type({ L"literal", L"literal", L"literal" }), L"lyliteral");
	ASSERT_PARSE_FAILURE(Exa1, L"");
}
TEST("Exactly", "Parse Exactly<AnyOf>")
{
	using array_type = std::array<Output<wchar_t>, 5>;
	ASSERT_PARSE_SUCCESS(Exa2, L"abcbaa", array_type({ L"a", L"b", L"c", L"b", L"a" }), L"a");
	ASSERT_PARSE_FAILURE(Exa2, L"fedcba");
	ASSERT_PARSE_SUCCESS(Exa2, L"cbabcccbjklmnop", array_type({ L"c", L"b", L"a", L"b", L"c" }), L"ccbjklmnop");
	ASSERT_PARSE_FAILURE(Exa2, L"");
}
TEST("Exactly", "Parse Exactly<Choice>")
{
	using array_type = std::array<Output<wchar_t>, 4>;
	ASSERT_PARSE_SUCCESS(Exa3, L"abliteralcbliteralcf", array_type({ L"a", L"b", L"literal", L"c" }), L"bliteralcf");
	ASSERT_PARSE_SUCCESS(Exa3, L"abliteralcblitralcf", array_type({ L"a", L"b", L"literal", L"c" }), L"blitralcf");
	ASSERT_PARSE_SUCCESS(Exa3, L"literalabacliteral", array_type({ L"literal", L"a", L"b", L"a" }), L"cliteral");
	ASSERT_PARSE_FAILURE(Exa3, L"");
}
TEST("Exactly", "Parse Exactly<Sequence>")
{
	using array_type = std::array<std::tuple<Output<wchar_t>, Output<wchar_t>>, 2>;
	ASSERT_PARSE_SUCCESS(Exa4, L"literalaliteralcliteralcliteralb", array_type({ {L"literal", L"a"}, {L"literal", L"c"} }), L"literalcliteralb");
	ASSERT_PARSE_SUCCESS(Exa4, L"literalaliteralcliteralcliteralbliteral", array_type({ {L"literal", L"a"}, {L"literal", L"c"} }), L"literalcliteralbliteral");
	ASSERT_PARSE_FAILURE(Exa4, L"aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Exa4, L"");
}
