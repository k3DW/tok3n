// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("zero_or_more_parser");

TEST("zero_or_more_parser", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Zom1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Zom2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Zom3, value_type);
	ASSERT_PARSER_VALUE_TYPE(Zom4, value_type);

	ASSERT_IS_PARSER(Zom1, char, zero_or_more_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Zom2, char, zero_or_more_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Zom3, char, zero_or_more_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Zom4, char, zero_or_more_family, std::vector<std::tuple<output_span<char>, output_span<char>>>);

	ASSERT_IS_PARSER(Zom1, wchar_t, zero_or_more_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Zom2, wchar_t, zero_or_more_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Zom3, wchar_t, zero_or_more_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Zom4, wchar_t, zero_or_more_family, std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>);

	ASSERT_IS_PARSER(Zom1, int, zero_or_more_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Zom2, int, zero_or_more_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Zom3, int, zero_or_more_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Zom4, int, zero_or_more_family, std::vector<std::tuple<output_span<int>, output_span<int>>>);
}

TEST("zero_or_more_parser", "Parse zero_or_more_parser<all_of_parser>")
{
	{
		using vec_type = std::vector<output_span<char>>;
		ASSERT_PARSE_SUCCESS(Zom1, "litera", vec_type{}, "litera");
		ASSERT_PARSE_SUCCESS(Zom1, "literal", vec_type({ "literal" }), "");
		ASSERT_PARSE_SUCCESS(Zom1, "literally", vec_type({ "literal" }), "ly");
		ASSERT_PARSE_SUCCESS(Zom1, "literallitera", vec_type({ "literal" }), "litera");
		ASSERT_PARSE_SUCCESS(Zom1, "literalliterallitera", vec_type({ "literal", "literal" }), "litera");
		ASSERT_PARSE_SUCCESS(Zom1, " literalliterallitera", vec_type{}, " literalliterallitera");
		ASSERT_PARSE_SUCCESS(Zom1, "", vec_type{}, "");
	}

	{
		using vec_type = std::vector<output_span<wchar_t>>;
		ASSERT_PARSE_SUCCESS(Zom1, L"litera", vec_type{}, L"litera");
		ASSERT_PARSE_SUCCESS(Zom1, L"literal", vec_type({ L"literal" }), L"");
		ASSERT_PARSE_SUCCESS(Zom1, L"literally", vec_type({ L"literal" }), L"ly");
		ASSERT_PARSE_SUCCESS(Zom1, L"literallitera", vec_type({ L"literal" }), L"litera");
		ASSERT_PARSE_SUCCESS(Zom1, L"literalliterallitera", vec_type({ L"literal", L"literal" }), L"litera");
		ASSERT_PARSE_SUCCESS(Zom1, L" literalliterallitera", vec_type{}, L" literalliterallitera");
		ASSERT_PARSE_SUCCESS(Zom1, L"", vec_type{}, L"");
	}

	{
		using vec_type = std::vector<output_span<int>>;
		ASSERT_PARSE_SUCCESS(Zom1, e<int>("litera"), vec_type{}, e<int>("litera"));
		ASSERT_PARSE_SUCCESS(Zom1, e<int>("literal"), vec_type({ e<int>("literal") }), e<int>(""));
		ASSERT_PARSE_SUCCESS(Zom1, e<int>("literally"), vec_type({ e<int>("literal") }), e<int>("ly"));
		ASSERT_PARSE_SUCCESS(Zom1, e<int>("literallitera"), vec_type({ e<int>("literal") }), e<int>("litera"));
		ASSERT_PARSE_SUCCESS(Zom1, e<int>("literalliterallitera"), vec_type({ e<int>("literal"), e<int>("literal") }), e<int>("litera"));
		ASSERT_PARSE_SUCCESS(Zom1, e<int>(" literalliterallitera"), vec_type{}, e<int>(" literalliterallitera"));
		ASSERT_PARSE_SUCCESS(Zom1, e<int>(""), vec_type{}, e<int>(""));
	}
}
TEST("zero_or_more_parser", "Parse zero_or_more_parser<any_of_parser>")
{
	{
		using vec_type = std::vector<output_span<char>>;
		ASSERT_PARSE_SUCCESS(Zom2, "abcdef", vec_type({ "a", "b", "c" }), "def");
		ASSERT_PARSE_SUCCESS(Zom2, "fedcba", vec_type{}, "fedcba");
		ASSERT_PARSE_SUCCESS(Zom2, "cbabcccbjklmnop", vec_type({ "c", "b", "a", "b", "c", "c", "c", "b" }), "jklmnop");
		ASSERT_PARSE_SUCCESS(Zom2, "", vec_type{}, "");
	}

	{
		using vec_type = std::vector<output_span<wchar_t>>;
		ASSERT_PARSE_SUCCESS(Zom2, L"abcdef", vec_type({ L"a", L"b", L"c" }), L"def");
		ASSERT_PARSE_SUCCESS(Zom2, L"fedcba", vec_type{}, L"fedcba");
		ASSERT_PARSE_SUCCESS(Zom2, L"cbabcccbjklmnop", vec_type({ L"c", L"b", L"a", L"b", L"c", L"c", L"c", L"b" }), L"jklmnop");
		ASSERT_PARSE_SUCCESS(Zom2, L"", vec_type{}, L"");
	}

	{
		using vec_type = std::vector<output_span<int>>;
		ASSERT_PARSE_SUCCESS(Zom2, e<int>("abcdef"), vec_type({ e<int>("a"), e<int>("b"), e<int>("c") }), e<int>("def"));
		ASSERT_PARSE_SUCCESS(Zom2, e<int>("fedcba"), vec_type{}, e<int>("fedcba"));
		ASSERT_PARSE_SUCCESS(Zom2, e<int>("cbabcccbjklmnop"), vec_type({ e<int>("c"), e<int>("b"), e<int>("a"), e<int>("b"), e<int>("c"), e<int>("c"), e<int>("c"), e<int>("b") }), e<int>("jklmnop"));
		ASSERT_PARSE_SUCCESS(Zom2, e<int>(""), vec_type{}, e<int>(""));
	}
}
TEST("zero_or_more_parser", "Parse zero_or_more_parser<choice_parser>")
{
	{
		using vec_type = std::vector<output_span<char>>;
		// ICE: ASSERT_PARSE_SUCCESS(Zom3, "abliteralcbliteralcf", vec_type({ "a", "b", "literal", "c", "b", "literal", "c" }), "f");
		ASSERT_PARSE_SUCCESS(Zom3, "abliteralcblitralcf", vec_type({ "a", "b", "literal", "c", "b" }), "litralcf");
		// ICE: ASSERT_PARSE_SUCCESS(Zom3, "literalabacliteral", vec_type({ "literal", "a", "b", "a", "c", "literal" }), "");
		ASSERT_PARSE_SUCCESS(Zom3, "", vec_type{}, "");
	}

	{
		using vec_type = std::vector<output_span<wchar_t>>;
		// ICE: ASSERT_PARSE_SUCCESS(Zom3, L"abliteralcbliteralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b", L"literal", L"c" }), L"f");
		ASSERT_PARSE_SUCCESS(Zom3, L"abliteralcblitralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b" }), L"litralcf");
		// ICE: ASSERT_PARSE_SUCCESS(Zom3, L"literalabacliteral", vec_type({ L"literal", L"a", L"b", L"a", L"c", L"literal" }), L"");
		ASSERT_PARSE_SUCCESS(Zom3, L"", vec_type{}, L"");
	}

	{
		using vec_type = std::vector<output_span<int>>;
		// ICE: ASSERT_PARSE_SUCCESS(Zom3, e<int>("abliteralcbliteralcf"), vec_type({ e<int>("a"), e<int>("b"), e<int>("literal"), e<int>("c"), e<int>("b"), e<int>("literal"), e<int>("c") }), e<int>("f"));
		ASSERT_PARSE_SUCCESS(Zom3, e<int>("abliteralcblitralcf"), vec_type({ e<int>("a"), e<int>("b"), e<int>("literal"), e<int>("c"), e<int>("b") }), e<int>("litralcf"));
		// ICE: ASSERT_PARSE_SUCCESS(Zom3, e<int>("literalabacliteral"), vec_type({ e<int>("literal"), e<int>("a"), e<int>("b"), e<int>("a"), e<int>("c"), e<int>("literal") }), e<int>(""));
		ASSERT_PARSE_SUCCESS(Zom3, e<int>(""), vec_type{}, e<int>(""));
	}
}
TEST("zero_or_more_parser", "Parse zero_or_more_parser<sequence_parser>")
{
	{
		using vec_type = std::vector<std::tuple<output_span<char>, output_span<char>>>;
		ASSERT_PARSE_SUCCESS(Zom4, "literalaliteralcliteralcliteralb", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), "");
		ASSERT_PARSE_SUCCESS(Zom4, "literalaliteralcliteralcliteralbliteral", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), "literal");
		ASSERT_PARSE_SUCCESS(Zom4, "aliteralaliteralcliteralbliteral", vec_type{}, "aliteralaliteralcliteralbliteral");
		ASSERT_PARSE_SUCCESS(Zom4, "", vec_type{}, "");
	}

	{
		using vec_type = std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>;
		ASSERT_PARSE_SUCCESS(Zom4, L"literalaliteralcliteralcliteralb", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L"");
		ASSERT_PARSE_SUCCESS(Zom4, L"literalaliteralcliteralcliteralbliteral", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L"literal");
		ASSERT_PARSE_SUCCESS(Zom4, L"aliteralaliteralcliteralbliteral", vec_type{}, L"aliteralaliteralcliteralbliteral");
		ASSERT_PARSE_SUCCESS(Zom4, L"", vec_type{}, L"");
	}

	{
		using vec_type = std::vector<std::tuple<output_span<int>, output_span<int>>>;
		ASSERT_PARSE_SUCCESS(Zom4, e<int>("literalaliteralcliteralcliteralb"), vec_type({ {e<int>("literal"), e<int>("a")}, {e<int>("literal"), e<int>("c")}, {e<int>("literal"), e<int>("c")}, {e<int>("literal"), e<int>("b")} }), e<int>(""));
		ASSERT_PARSE_SUCCESS(Zom4, e<int>("literalaliteralcliteralcliteralbliteral"), vec_type({ {e<int>("literal"), e<int>("a")}, {e<int>("literal"), e<int>("c")}, {e<int>("literal"), e<int>("c")}, {e<int>("literal"), e<int>("b")} }), e<int>("literal"));
		ASSERT_PARSE_SUCCESS(Zom4, e<int>("aliteralaliteralcliteralbliteral"), vec_type{}, e<int>("aliteralaliteralcliteralbliteral"));
		ASSERT_PARSE_SUCCESS(Zom4, e<int>(""), vec_type{}, e<int>(""));
	}
}

TEST("zero_or_more_parser", "Parse zero_or_more_parser<void-parser>")
{
	using P = zero_or_more_parser<ignore_parser<ABC>>;

	ASSERT_PARSE_SUCCESS_VOID(P, "abcabcabca", "a");
	ASSERT_PARSE_SUCCESS_VOID(P, "abcabca", "a");
	ASSERT_PARSE_SUCCESS_VOID(P, "abcabc", "");
	ASSERT_PARSE_SUCCESS_VOID(P, " abcabc", " abcabc");
	ASSERT_PARSE_SUCCESS_VOID(P, "abcab", "ab");
	ASSERT_PARSE_SUCCESS_VOID(P, "abc", "");
	ASSERT_PARSE_SUCCESS_VOID(P, "", "");

	ASSERT_PARSE_SUCCESS_VOID(P, L"abcabcabca", L"a");
	ASSERT_PARSE_SUCCESS_VOID(P, L"abcabca", L"a");
	ASSERT_PARSE_SUCCESS_VOID(P, L"abcabc", L"");
	ASSERT_PARSE_SUCCESS_VOID(P, L" abcabc", L" abcabc");
	ASSERT_PARSE_SUCCESS_VOID(P, L"abcab", L"ab");
	ASSERT_PARSE_SUCCESS_VOID(P, L"abc", L"");
	ASSERT_PARSE_SUCCESS_VOID(P, L"", L"");

	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabcabca"), e<int>("a"));
	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabca"), e<int>("a"));
	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabc"), e<int>(""));
	ASSERT_PARSE_SUCCESS_VOID(P, e<int>(" abcabc"), e<int>(" abcabc"));
	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcab"), e<int>("ab"));
	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abc"), e<int>(""));
	ASSERT_PARSE_SUCCESS_VOID(P, e<int>(""), e<int>(""));
}
