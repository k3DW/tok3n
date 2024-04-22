#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("Maybe");

TEST("Maybe", "Requirements")
{
	ASSERT_IS_PARSER(May1, wchar_t, MaybeFamily, std::optional<Output<wchar_t>>);
	ASSERT_IS_PARSER(May2, wchar_t, MaybeFamily, std::optional<Output<wchar_t>>);
	ASSERT_IS_PARSER(May3, wchar_t, MaybeFamily, std::optional<Output<wchar_t>>);
	ASSERT_IS_PARSER(May4, wchar_t, MaybeFamily, std::optional<std::tuple<Output<wchar_t>, Output<wchar_t>>>);
}

TEST("Maybe", "Parse Maybe<AllOf>")
{
	ASSERT_PARSE_SUCCESS(May1, L"litera", std::nullopt, L"litera");
	ASSERT_PARSE_SUCCESS(May1, L"literal", std::optional(L"literal"), L"");
	ASSERT_PARSE_SUCCESS(May1, L"literally", std::optional(L"literal"), L"ly");
	ASSERT_PARSE_SUCCESS(May1, L"literallitera", std::optional(L"literal"), L"litera");
	ASSERT_PARSE_SUCCESS(May1, L"literalliterallitera", std::optional(L"literal"), L"literallitera");
	ASSERT_PARSE_SUCCESS(May1, L" literalliterallitera", std::nullopt, L" literalliterallitera");
	ASSERT_PARSE_SUCCESS(May1, L"", std::nullopt, L"");
}
TEST("Maybe", "Parse Maybe<AnyOf>")
{
	ASSERT_PARSE_SUCCESS(May2, L"abcdef", std::optional(L"a"), L"bcdef");
	ASSERT_PARSE_SUCCESS(May2, L"fedcba", std::nullopt, L"fedcba");
	ASSERT_PARSE_SUCCESS(May2, L"cbabcccbjklmnop", std::optional(L"c"), L"babcccbjklmnop");
	ASSERT_PARSE_SUCCESS(May2, L"", std::nullopt, L"");
}
TEST("Maybe", "Parse Maybe<Choice>")
{
	ASSERT_PARSE_SUCCESS(May3, L"abliteralcbliteralcf", std::optional(L"a"), L"bliteralcbliteralcf");
	ASSERT_PARSE_SUCCESS(May3, L"abliteralcblitralcf", std::optional(L"a"), L"bliteralcblitralcf");
	ASSERT_PARSE_SUCCESS(May3, L"literalabacliteral", std::optional(L"literal"), L"abacliteral");
	ASSERT_PARSE_SUCCESS(May3, L"", std::nullopt, L"");
}
TEST("Maybe", "Parse Maybe<Sequence>")
{
	ASSERT_PARSE_SUCCESS(May4, L"literalaliteralcliteralcliteralb", std::optional(std::tuple(L"literal", L"a")), L"literalcliteralcliteralb");
	ASSERT_PARSE_SUCCESS(May4, L"literalaliteralcliteralcliteralbliteral", std::optional(std::tuple(L"literal", L"a")), L"literalcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(May4, L"aliteralaliteralcliteralbliteral", std::nullopt, L"aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(May4, L"", std::nullopt, L"");
}
