#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("Complete");

TEST("Complete", "Requirements")
{
	ASSERT_IS_PARSER(Com1, wchar_t, CompleteFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Com2, wchar_t, CompleteFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Com3, wchar_t, CompleteFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Com4, wchar_t, CompleteFamily, std::tuple<Output<wchar_t>, Output<wchar_t>>);
	ASSERT_IS_PARSER(Com5, wchar_t, CompleteFamily, std::optional<std::tuple<Output<wchar_t>, Output<wchar_t>>>);
	ASSERT_IS_PARSER(Com6, wchar_t, CompleteFamily, std::vector<std::tuple<Output<wchar_t>, Output<wchar_t>>>);
	ASSERT_IS_PARSER(Com7, wchar_t, CompleteFamily, std::vector<std::tuple<Output<wchar_t>, Output<wchar_t>>>);
}

TEST("Complete", "Complete<AllOf>")
{
	ASSERT_PARSE_FAILURE(Com1, L"litera");
	ASSERT_PARSE_SUCCESS(Com1, L"literal", L"literal", L"");
	ASSERT_PARSE_FAILURE(Com1, L"literally");
	ASSERT_PARSE_FAILURE(Com1, L"literallitera");
	ASSERT_PARSE_FAILURE(Com1, L"literalliterallitera");
	ASSERT_PARSE_FAILURE(Com1, L" literalliterallitera");
	ASSERT_PARSE_FAILURE(Com1, L"");
}
TEST("Complete", "Complete<AnyOf>")
{
	ASSERT_PARSE_SUCCESS(Com2, L"a", L"a", L"");
	ASSERT_PARSE_SUCCESS(Com2, L"b", L"b", L"");
	ASSERT_PARSE_FAILURE(Com2, L"abcdef");
	ASSERT_PARSE_FAILURE(Com2, L"fedcba");
	ASSERT_PARSE_FAILURE(Com2, L"cbabcccbjklmnop");
	ASSERT_PARSE_FAILURE(Com2, L"");
}
TEST("Complete", "Complete<Choice>")
{
	ASSERT_PARSE_FAILURE(Com3, L"abliteralcbliteralcf");
	ASSERT_PARSE_FAILURE(Com3, L"abliteralcblitralcf");
	ASSERT_PARSE_FAILURE(Com3, L"literalabacliteral");
	ASSERT_PARSE_SUCCESS(Com3, L"literal", L"literal", L"");
	ASSERT_PARSE_SUCCESS(Com3, L"a", L"a", L"");
	ASSERT_PARSE_SUCCESS(Com3, L"b", L"b", L"");
	ASSERT_PARSE_FAILURE(Com3, L"");
}
TEST("Complete", "Complete<Sequence>")
{
	ASSERT_PARSE_FAILURE(Com4, L"literalaliteralcliteralcliteralb");
	ASSERT_PARSE_FAILURE(Com4, L"literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com4, L"literala", std::tuple(L"literal", L"a"), L"");
	ASSERT_PARSE_SUCCESS(Com4, L"literalb", std::tuple(L"literal", L"b"), L"");
	ASSERT_PARSE_FAILURE(Com4, L"literald");
	ASSERT_PARSE_FAILURE(Com4, L"aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Com4, L"");
}
TEST("Complete", "Complete<Maybe>")
{
	ASSERT_PARSE_FAILURE(Com5, L"literalaliteralcliteralcliteralb");
	ASSERT_PARSE_FAILURE(Com5, L"literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com5, L"literala", std::optional(std::tuple(L"literal", L"a")), L"");
	ASSERT_PARSE_SUCCESS(Com5, L"literalb", std::optional(std::tuple(L"literal", L"b")), L"");
	ASSERT_PARSE_FAILURE(Com5, L"literald");
	ASSERT_PARSE_FAILURE(Com5, L"aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com5, L"", std::nullopt, L"");
}
TEST("Complete", "Complete<OneOrMore>")
{
	ASSERT_PARSE_SUCCESS(Com6, L"literalaliteralcliteralcliteralb", Com6::result_for<wchar_t>({ { L"literal", L"a" }, { L"literal", L"c" }, { L"literal", L"c" }, { L"literal", L"b" } }), L"");
	ASSERT_PARSE_FAILURE(Com6, L"literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com6, L"literala", Com6::result_for<wchar_t>({ { L"literal", L"a" } }), L"");
	ASSERT_PARSE_SUCCESS(Com6, L"literalb", Com6::result_for<wchar_t>({ { L"literal", L"b" } }), L"");
	ASSERT_PARSE_FAILURE(Com6, L"literald");
	ASSERT_PARSE_FAILURE(Com6, L"aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Com6, L"");
}
TEST("Complete", "Complete<ZeroOrMore>")
{
	ASSERT_PARSE_SUCCESS(Com7, L"literalaliteralcliteralcliteralb", Com7::result_for<wchar_t>({ { L"literal", L"a" }, { L"literal", L"c" }, { L"literal", L"c" }, { L"literal", L"b" } }), L"");
	ASSERT_PARSE_FAILURE(Com7, L"literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com7, L"literala", Com7::result_for<wchar_t>({ { L"literal", L"a" } }), L"");
	ASSERT_PARSE_SUCCESS(Com7, L"literalb", Com7::result_for<wchar_t>({ { L"literal", L"b" } }), L"");
	ASSERT_PARSE_FAILURE(Com7, L"literald");
	ASSERT_PARSE_FAILURE(Com7, L"aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com7, L"", Com7::result_for<wchar_t>{}, L"");
}
