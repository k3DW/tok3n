#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("complete_parser");

TEST("complete_parser", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Com1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Com2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Com3, value_type);
	ASSERT_PARSER_VALUE_TYPE(Com4, value_type);
	ASSERT_PARSER_VALUE_TYPE(Com5, value_type);
	ASSERT_PARSER_VALUE_TYPE(Com6, value_type);
	ASSERT_PARSER_VALUE_TYPE(Com7, value_type);

	ASSERT_IS_PARSER(Com1, char, complete_family, output_span<char>);
	ASSERT_IS_PARSER(Com2, char, complete_family, output_span<char>);
	ASSERT_IS_PARSER(Com3, char, complete_family, output_span<char>);
	ASSERT_IS_PARSER(Com4, char, complete_family, std::tuple<output_span<char>, output_span<char>>);
	ASSERT_IS_PARSER(Com5, char, complete_family, std::optional<std::tuple<output_span<char>, output_span<char>>>);
	ASSERT_IS_PARSER(Com6, char, complete_family, std::vector<std::tuple<output_span<char>, output_span<char>>>);
	ASSERT_IS_PARSER(Com7, char, complete_family, std::vector<std::tuple<output_span<char>, output_span<char>>>);

	ASSERT_IS_PARSER(Com1, wchar_t, complete_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(Com2, wchar_t, complete_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(Com3, wchar_t, complete_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(Com4, wchar_t, complete_family, std::tuple<output_span<wchar_t>, output_span<wchar_t>>);
	ASSERT_IS_PARSER(Com5, wchar_t, complete_family, std::optional<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>);
	ASSERT_IS_PARSER(Com6, wchar_t, complete_family, std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>);
	ASSERT_IS_PARSER(Com7, wchar_t, complete_family, std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>);
	
	ASSERT_IS_PARSER(Com1, int, complete_family, output_span<int>);
	ASSERT_IS_PARSER(Com2, int, complete_family, output_span<int>);
	ASSERT_IS_PARSER(Com3, int, complete_family, output_span<int>);
	ASSERT_IS_PARSER(Com4, int, complete_family, std::tuple<output_span<int>, output_span<int>>);
	ASSERT_IS_PARSER(Com5, int, complete_family, std::optional<std::tuple<output_span<int>, output_span<int>>>);
	ASSERT_IS_PARSER(Com6, int, complete_family, std::vector<std::tuple<output_span<int>, output_span<int>>>);
	ASSERT_IS_PARSER(Com7, int, complete_family, std::vector<std::tuple<output_span<int>, output_span<int>>>);
}

TEST("complete_parser", "complete_parser<all_of_parser>")
{
	ASSERT_PARSE_FAILURE(Com1, "litera");
	ASSERT_PARSE_SUCCESS(Com1, "literal", "literal", "");
	ASSERT_PARSE_FAILURE(Com1, "literally");
	ASSERT_PARSE_FAILURE(Com1, "literallitera");
	ASSERT_PARSE_FAILURE(Com1, "literalliterallitera");
	ASSERT_PARSE_FAILURE(Com1, " literalliterallitera");
	ASSERT_PARSE_FAILURE(Com1, "");

	ASSERT_PARSE_FAILURE(Com1, L"litera");
	ASSERT_PARSE_SUCCESS(Com1, L"literal", L"literal", L"");
	ASSERT_PARSE_FAILURE(Com1, L"literally");
	ASSERT_PARSE_FAILURE(Com1, L"literallitera");
	ASSERT_PARSE_FAILURE(Com1, L"literalliterallitera");
	ASSERT_PARSE_FAILURE(Com1, L" literalliterallitera");
	ASSERT_PARSE_FAILURE(Com1, L"");

	ASSERT_PARSE_FAILURE(Com1, e<int>("litera"));
	ASSERT_PARSE_SUCCESS(Com1, e<int>("literal"), e<int>("literal"), e<int>());
	ASSERT_PARSE_FAILURE(Com1, e<int>("literally"));
	ASSERT_PARSE_FAILURE(Com1, e<int>("literallitera"));
	ASSERT_PARSE_FAILURE(Com1, e<int>("literalliterallitera"));
	ASSERT_PARSE_FAILURE(Com1, e<int>(" literalliterallitera"));
	ASSERT_PARSE_FAILURE(Com1, e<int>());
}
TEST("complete_parser", "complete_parser<any_of_parser>")
{
	ASSERT_PARSE_SUCCESS(Com2, "a", "a", "");
	ASSERT_PARSE_SUCCESS(Com2, "b", "b", "");
	ASSERT_PARSE_FAILURE(Com2, "abcdef");
	ASSERT_PARSE_FAILURE(Com2, "fedcba");
	ASSERT_PARSE_FAILURE(Com2, "cbabcccbjklmnop");
	ASSERT_PARSE_FAILURE(Com2, "");

	ASSERT_PARSE_SUCCESS(Com2, L"a", L"a", L"");
	ASSERT_PARSE_SUCCESS(Com2, L"b", L"b", L"");
	ASSERT_PARSE_FAILURE(Com2, L"abcdef");
	ASSERT_PARSE_FAILURE(Com2, L"fedcba");
	ASSERT_PARSE_FAILURE(Com2, L"cbabcccbjklmnop");
	ASSERT_PARSE_FAILURE(Com2, L"");

	ASSERT_PARSE_SUCCESS(Com2, e<int>("a"), e<int>("a"), e<int>());
	ASSERT_PARSE_SUCCESS(Com2, e<int>("b"), e<int>("b"), e<int>());
	ASSERT_PARSE_FAILURE(Com2, e<int>("abcdef"));
	ASSERT_PARSE_FAILURE(Com2, e<int>("fedcba"));
	ASSERT_PARSE_FAILURE(Com2, e<int>("cbabcccbjklmnop"));
	ASSERT_PARSE_FAILURE(Com2, e<int>());
}
TEST("complete_parser", "complete_parser<Choice>")
{
	ASSERT_PARSE_FAILURE(Com3, "abliteralcbliteralcf");
	ASSERT_PARSE_FAILURE(Com3, "abliteralcblitralcf");
	ASSERT_PARSE_FAILURE(Com3, "literalabacliteral");
	ASSERT_PARSE_SUCCESS(Com3, "literal", "literal", "");
	ASSERT_PARSE_SUCCESS(Com3, "a", "a", "");
	ASSERT_PARSE_SUCCESS(Com3, "b", "b", "");
	ASSERT_PARSE_FAILURE(Com3, "");

	ASSERT_PARSE_FAILURE(Com3, L"abliteralcbliteralcf");
	ASSERT_PARSE_FAILURE(Com3, L"abliteralcblitralcf");
	ASSERT_PARSE_FAILURE(Com3, L"literalabacliteral");
	ASSERT_PARSE_SUCCESS(Com3, L"literal", L"literal", L"");
	ASSERT_PARSE_SUCCESS(Com3, L"a", L"a", L"");
	ASSERT_PARSE_SUCCESS(Com3, L"b", L"b", L"");
	ASSERT_PARSE_FAILURE(Com3, L"");

	ASSERT_PARSE_FAILURE(Com3, e<int>("abliteralcbliteralcf"));
	ASSERT_PARSE_FAILURE(Com3, e<int>("abliteralcblitralcf"));
	ASSERT_PARSE_FAILURE(Com3, e<int>("literalabacliteral"));
	ASSERT_PARSE_SUCCESS(Com3, e<int>("literal"), e<int>("literal"), e<int>());
	ASSERT_PARSE_SUCCESS(Com3, e<int>("a"), e<int>("a"), e<int>());
	ASSERT_PARSE_SUCCESS(Com3, e<int>("b"), e<int>("b"), e<int>());
	ASSERT_PARSE_FAILURE(Com3, e<int>());
}
TEST("complete_parser", "complete_parser<Sequence>")
{
	ASSERT_PARSE_FAILURE(Com4, "literalaliteralcliteralcliteralb");
	ASSERT_PARSE_FAILURE(Com4, "literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com4, "literala", std::tuple("literal", "a"), "");
	ASSERT_PARSE_SUCCESS(Com4, "literalb", std::tuple("literal", "b"), "");
	ASSERT_PARSE_FAILURE(Com4, "literald");
	ASSERT_PARSE_FAILURE(Com4, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Com4, "");

	ASSERT_PARSE_FAILURE(Com4, L"literalaliteralcliteralcliteralb");
	ASSERT_PARSE_FAILURE(Com4, L"literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com4, L"literala", std::tuple(L"literal", L"a"), L"");
	ASSERT_PARSE_SUCCESS(Com4, L"literalb", std::tuple(L"literal", L"b"), L"");
	ASSERT_PARSE_FAILURE(Com4, L"literald");
	ASSERT_PARSE_FAILURE(Com4, L"aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Com4, L"");

	ASSERT_PARSE_FAILURE(Com4, e<int>("literalaliteralcliteralcliteralb"));
	ASSERT_PARSE_FAILURE(Com4, e<int>("literalaliteralcliteralcliteralbliteral"));
	ASSERT_PARSE_SUCCESS(Com4, e<int>("literala"), std::tuple(e<int>("literal"), e<int>("a")), e<int>());
	ASSERT_PARSE_SUCCESS(Com4, e<int>("literalb"), std::tuple(e<int>("literal"), e<int>("b")), e<int>());
	ASSERT_PARSE_FAILURE(Com4, e<int>("literald"));
	ASSERT_PARSE_FAILURE(Com4, e<int>("aliteralaliteralcliteralbliteral"));
	ASSERT_PARSE_FAILURE(Com4, e<int>());
}
TEST("complete_parser", "complete_parser<Maybe>")
{
	ASSERT_PARSE_FAILURE(Com5, "literalaliteralcliteralcliteralb");
	ASSERT_PARSE_FAILURE(Com5, "literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com5, "literala", std::optional(std::tuple("literal", "a")), "");
	ASSERT_PARSE_SUCCESS(Com5, "literalb", std::optional(std::tuple("literal", "b")), "");
	ASSERT_PARSE_FAILURE(Com5, "literald");
	ASSERT_PARSE_FAILURE(Com5, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com5, "", std::nullopt, "");

	ASSERT_PARSE_FAILURE(Com5, L"literalaliteralcliteralcliteralb");
	ASSERT_PARSE_FAILURE(Com5, L"literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com5, L"literala", std::optional(std::tuple(L"literal", L"a")), L"");
	ASSERT_PARSE_SUCCESS(Com5, L"literalb", std::optional(std::tuple(L"literal", L"b")), L"");
	ASSERT_PARSE_FAILURE(Com5, L"literald");
	ASSERT_PARSE_FAILURE(Com5, L"aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com5, L"", std::nullopt, L"");

	ASSERT_PARSE_FAILURE(Com5, e<int>("literalaliteralcliteralcliteralb"));
	ASSERT_PARSE_FAILURE(Com5, e<int>("literalaliteralcliteralcliteralbliteral"));
	ASSERT_PARSE_SUCCESS(Com5, e<int>("literala"), std::optional(std::tuple(e<int>("literal"), e<int>("a"))), e<int>());
	ASSERT_PARSE_SUCCESS(Com5, e<int>("literalb"), std::optional(std::tuple(e<int>("literal"), e<int>("b"))), e<int>());
	ASSERT_PARSE_FAILURE(Com5, e<int>("literald"));
	ASSERT_PARSE_FAILURE(Com5, e<int>("aliteralaliteralcliteralbliteral"));
	ASSERT_PARSE_SUCCESS(Com5, e<int>(), std::nullopt, e<int>());
}
TEST("complete_parser", "complete_parser<OneOrMore>")
{
	ASSERT_PARSE_SUCCESS(Com6, "literalaliteralcliteralcliteralb", Com6::result_for<char>({ { "literal", "a" }, { "literal", "c" }, { "literal", "c" }, { "literal", "b" } }), "");
	ASSERT_PARSE_FAILURE(Com6, "literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com6, "literala", Com6::result_for<char>({ { "literal", "a" } }), "");
	ASSERT_PARSE_SUCCESS(Com6, "literalb", Com6::result_for<char>({ { "literal", "b" } }), "");
	ASSERT_PARSE_FAILURE(Com6, "literald");
	ASSERT_PARSE_FAILURE(Com6, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Com6, "");

	ASSERT_PARSE_SUCCESS(Com6, L"literalaliteralcliteralcliteralb", Com6::result_for<wchar_t>({ { L"literal", L"a" }, { L"literal", L"c" }, { L"literal", L"c" }, { L"literal", L"b" } }), L"");
	ASSERT_PARSE_FAILURE(Com6, L"literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com6, L"literala", Com6::result_for<wchar_t>({ { L"literal", L"a" } }), L"");
	ASSERT_PARSE_SUCCESS(Com6, L"literalb", Com6::result_for<wchar_t>({ { L"literal", L"b" } }), L"");
	ASSERT_PARSE_FAILURE(Com6, L"literald");
	ASSERT_PARSE_FAILURE(Com6, L"aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_FAILURE(Com6, L"");

	ASSERT_PARSE_SUCCESS(Com6, e<int>("literalaliteralcliteralcliteralb"), Com6::result_for<int>({ { e<int>("literal"), e<int>("a") }, { e<int>("literal"), e<int>("c") }, { e<int>("literal"), e<int>("c") }, { e<int>("literal"), e<int>("b") } }), e<int>());
	ASSERT_PARSE_FAILURE(Com6, e<int>("literalaliteralcliteralcliteralbliteral"));
	ASSERT_PARSE_SUCCESS(Com6, e<int>("literala"), Com6::result_for<int>({ { e<int>("literal"), e<int>("a") } }), e<int>());
	ASSERT_PARSE_SUCCESS(Com6, e<int>("literalb"), Com6::result_for<int>({ { e<int>("literal"), e<int>("b") } }), e<int>());
	ASSERT_PARSE_FAILURE(Com6, e<int>("literald"));
	ASSERT_PARSE_FAILURE(Com6, e<int>("aliteralaliteralcliteralbliteral"));
	ASSERT_PARSE_FAILURE(Com6, e<int>());
}
TEST("complete_parser", "complete_parser<ZeroOrMore>")
{
	ASSERT_PARSE_SUCCESS(Com7, "literalaliteralcliteralcliteralb", Com7::result_for<char>({ { "literal", "a" }, { "literal", "c" }, { "literal", "c" }, { "literal", "b" } }), "");
	ASSERT_PARSE_FAILURE(Com7, "literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com7, "literala", Com7::result_for<char>({ { "literal", "a" } }), "");
	ASSERT_PARSE_SUCCESS(Com7, "literalb", Com7::result_for<char>({ { "literal", "b" } }), "");
	ASSERT_PARSE_FAILURE(Com7, "literald");
	ASSERT_PARSE_FAILURE(Com7, "aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com7, "", Com7::result_for<char>{}, "");

	ASSERT_PARSE_SUCCESS(Com7, L"literalaliteralcliteralcliteralb", Com7::result_for<wchar_t>({ { L"literal", L"a" }, { L"literal", L"c" }, { L"literal", L"c" }, { L"literal", L"b" } }), L"");
	ASSERT_PARSE_FAILURE(Com7, L"literalaliteralcliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com7, L"literala", Com7::result_for<wchar_t>({ { L"literal", L"a" } }), L"");
	ASSERT_PARSE_SUCCESS(Com7, L"literalb", Com7::result_for<wchar_t>({ { L"literal", L"b" } }), L"");
	ASSERT_PARSE_FAILURE(Com7, L"literald");
	ASSERT_PARSE_FAILURE(Com7, L"aliteralaliteralcliteralbliteral");
	ASSERT_PARSE_SUCCESS(Com7, L"", Com7::result_for<wchar_t>{}, L"");

	ASSERT_PARSE_SUCCESS(Com7, e<int>("literalaliteralcliteralcliteralb"), Com7::result_for<int>({ { e<int>("literal"), e<int>("a") }, { e<int>("literal"), e<int>("c") }, { e<int>("literal"), e<int>("c") }, { e<int>("literal"), e<int>("b") } }), e<int>());
	ASSERT_PARSE_FAILURE(Com7, e<int>("literalaliteralcliteralcliteralbliteral"));
	ASSERT_PARSE_SUCCESS(Com7, e<int>("literala"), Com7::result_for<int>({ { e<int>("literal"), e<int>("a") } }), e<int>());
	ASSERT_PARSE_SUCCESS(Com7, e<int>("literalb"), Com7::result_for<int>({ { e<int>("literal"), e<int>("b") } }), e<int>());
	ASSERT_PARSE_FAILURE(Com7, e<int>("literald"));
	ASSERT_PARSE_FAILURE(Com7, e<int>("aliteralaliteralcliteralbliteral"));
	ASSERT_PARSE_SUCCESS(Com7, e<int>(), Com7::result_for<int>{}, e<int>());
}
