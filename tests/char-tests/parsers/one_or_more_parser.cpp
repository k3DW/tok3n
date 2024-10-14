// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("one_or_more_parser");

TEST("one_or_more_parser", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Oom1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Oom2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Oom3, value_type);
	ASSERT_PARSER_VALUE_TYPE(Oom4, value_type);

	ASSERT_IS_PARSER(Oom1, char, one_or_more_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Oom2, char, one_or_more_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Oom3, char, one_or_more_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Oom4, char, one_or_more_family, std::vector<std::tuple<output_span<char>, output_span<char>>>);

	ASSERT_IS_PARSER(Oom1, wchar_t, one_or_more_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Oom2, wchar_t, one_or_more_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Oom3, wchar_t, one_or_more_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Oom4, wchar_t, one_or_more_family, std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>);

	ASSERT_IS_PARSER(Oom1, int, one_or_more_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Oom2, int, one_or_more_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Oom3, int, one_or_more_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Oom4, int, one_or_more_family, std::vector<std::tuple<output_span<int>, output_span<int>>>);
}

TEST("one_or_more_parser", "Parse one_or_more_parser<all_of_parser>")
{
	{
		using vec_type = std::vector<output_span<char>>;
		ASSERT_PARSE_FAILURE(Oom1, "litera");
		ASSERT_PARSE_SUCCESS(Oom1, "literal", vec_type({ "literal" }), "");
		ASSERT_PARSE_SUCCESS(Oom1, "literally", vec_type({ "literal" }), "ly");
		ASSERT_PARSE_SUCCESS(Oom1, "literallitera", vec_type({ "literal" }), "litera");
		ASSERT_PARSE_SUCCESS(Oom1, "literalliterallitera", vec_type({ "literal", "literal" }), "litera");
		ASSERT_PARSE_FAILURE(Oom1, " literalliterallitera");
		ASSERT_PARSE_FAILURE(Oom1, "");
	}

	{
		using vec_type = std::vector<output_span<wchar_t>>;
		ASSERT_PARSE_FAILURE(Oom1, L"litera");
		ASSERT_PARSE_SUCCESS(Oom1, L"literal", vec_type({ L"literal" }), L"");
		ASSERT_PARSE_SUCCESS(Oom1, L"literally", vec_type({ L"literal" }), L"ly");
		ASSERT_PARSE_SUCCESS(Oom1, L"literallitera", vec_type({ L"literal" }), L"litera");
		ASSERT_PARSE_SUCCESS(Oom1, L"literalliterallitera", vec_type({ L"literal", L"literal" }), L"litera");
		ASSERT_PARSE_FAILURE(Oom1, L" literalliterallitera");
		ASSERT_PARSE_FAILURE(Oom1, L"");
	}

	{
		using vec_type = std::vector<output_span<int>>;
		ASSERT_PARSE_FAILURE(Oom1, e<int>("litera"));
		ASSERT_PARSE_SUCCESS(Oom1, e<int>("literal"), vec_type({ e<int>("literal") }), e<int>(""));
		ASSERT_PARSE_SUCCESS(Oom1, e<int>("literally"), vec_type({ e<int>("literal") }), e<int>("ly"));
		ASSERT_PARSE_SUCCESS(Oom1, e<int>("literallitera"), vec_type({ e<int>("literal") }), e<int>("litera"));
		ASSERT_PARSE_SUCCESS(Oom1, e<int>("literalliterallitera"), vec_type({ e<int>("literal"), e<int>("literal") }), e<int>("litera"));
		ASSERT_PARSE_FAILURE(Oom1, e<int>(" literalliterallitera"));
		ASSERT_PARSE_FAILURE(Oom1, e<int>(""));
	}
}
TEST("one_or_more_parser", "Parse one_or_more_parser<any_of_parser>")
{
	{
		using vec_type = std::vector<output_span<char>>;
		ASSERT_PARSE_SUCCESS(Oom2, "abcdef", vec_type({ "a", "b", "c" }), "def");
		ASSERT_PARSE_FAILURE(Oom2, "fedcba");
		ASSERT_PARSE_SUCCESS(Oom2, "cbabcccbjklmnop", vec_type({ "c", "b", "a", "b", "c", "c", "c", "b" }), "jklmnop");
		ASSERT_PARSE_FAILURE(Oom2, "");
	}

	{
		using vec_type = std::vector<output_span<wchar_t>>;
		ASSERT_PARSE_SUCCESS(Oom2, L"abcdef", vec_type({ L"a", L"b", L"c" }), L"def");
		ASSERT_PARSE_FAILURE(Oom2, L"fedcba");
		ASSERT_PARSE_SUCCESS(Oom2, L"cbabcccbjklmnop", vec_type({ L"c", L"b", L"a", L"b", L"c", L"c", L"c", L"b" }), L"jklmnop");
		ASSERT_PARSE_FAILURE(Oom2, L"");
	}

	{
		using vec_type = std::vector<output_span<int>>;
		ASSERT_PARSE_SUCCESS(Oom2, e<int>("abcdef"), vec_type({ e<int>("a"), e<int>("b"), e<int>("c") }), e<int>("def"));
		ASSERT_PARSE_FAILURE(Oom2, e<int>("fedcba"));
		ASSERT_PARSE_SUCCESS(Oom2, e<int>("cbabcccbjklmnop"), vec_type({ e<int>("c"), e<int>("b"), e<int>("a"), e<int>("b"), e<int>("c"), e<int>("c"), e<int>("c"), e<int>("b") }), e<int>("jklmnop"));
		ASSERT_PARSE_FAILURE(Oom2, e<int>(""));
	}
}
TEST("one_or_more_parser", "Parse one_or_more_parser<choice_parser>")
{
	{
		using vec_type = std::vector<output_span<char>>;
		// ICE: ASSERT_PARSE_SUCCESS(Oom3, "abliteralcbliteralcf", vec_type({ "a", "b", "literal", "c", "b", "literal", "c" }), "f");
		ASSERT_PARSE_SUCCESS(Oom3, "abliteralcblitralcf", vec_type({ "a", "b", "literal", "c", "b" }), "litralcf");
		// ICE: ASSERT_PARSE_SUCCESS(Oom3, "literalabacliteral", vec_type({ "literal", "a", "b", "a", "c", "literal" }), "");
		ASSERT_PARSE_FAILURE(Oom3, "");
	}

	{
		using vec_type = std::vector<output_span<wchar_t>>;
		// ICE: ASSERT_PARSE_SUCCESS(Oom3, L"abliteralcbliteralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b", L"literal", L"c" }), L"f");
		ASSERT_PARSE_SUCCESS(Oom3, L"abliteralcblitralcf", vec_type({ L"a", L"b", L"literal", L"c", L"b" }), L"litralcf");
		// ICE: ASSERT_PARSE_SUCCESS(Oom3, L"literalabacliteral", vec_type({ L"literal", L"a", L"b", L"a", L"c", L"literal" }), L"");
		ASSERT_PARSE_FAILURE(Oom3, L"");
	}

	{
		using vec_type = std::vector<output_span<int>>;
		// ICE: ASSERT_PARSE_SUCCESS(Oom3, e<int>("abliteralcbliteralcf"), vec_type({ e<int>("a"), e<int>("b"), e<int>("literal"), e<int>("c"), e<int>("b"), e<int>("literal"), e<int>("c") }), e<int>("f"));
		ASSERT_PARSE_SUCCESS(Oom3, e<int>("abliteralcblitralcf"), vec_type({ e<int>("a"), e<int>("b"), e<int>("literal"), e<int>("c"), e<int>("b") }), e<int>("litralcf"));
		// ICE: ASSERT_PARSE_SUCCESS(Oom3, e<int>("literalabacliteral"), vec_type({ e<int>("literal"), e<int>("a"), e<int>("b"), e<int>("a"), e<int>("c"), e<int>("literal") }), e<int>(""));
		ASSERT_PARSE_FAILURE(Oom3, e<int>(""));
	}
}
TEST("one_or_more_parser", "Parse one_or_more_parser<sequence_parser>")
{
	{
		using vec_type = std::vector<std::tuple<output_span<char>, output_span<char>>>;
		ASSERT_PARSE_SUCCESS(Oom4, "literalaliteralcliteralcliteralb", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), "");
		ASSERT_PARSE_SUCCESS(Oom4, "literalaliteralcliteralcliteralbliteral", vec_type({ {"literal", "a"}, {"literal", "c"}, {"literal", "c"}, {"literal", "b"} }), "literal");
		ASSERT_PARSE_FAILURE(Oom4, "aliteralaliteralcliteralbliteral");
		ASSERT_PARSE_FAILURE(Oom4, "");
	}

	{
		using vec_type = std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>;
		ASSERT_PARSE_SUCCESS(Oom4, L"literalaliteralcliteralcliteralb", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L"");
		ASSERT_PARSE_SUCCESS(Oom4, L"literalaliteralcliteralcliteralbliteral", vec_type({ {L"literal", L"a"}, {L"literal", L"c"}, {L"literal", L"c"}, {L"literal", L"b"} }), L"literal");
		ASSERT_PARSE_FAILURE(Oom4, L"aliteralaliteralcliteralbliteral");
		ASSERT_PARSE_FAILURE(Oom4, L"");
	}

	{
		using vec_type = std::vector<std::tuple<output_span<int>, output_span<int>>>;
		ASSERT_PARSE_SUCCESS(Oom4, e<int>("literalaliteralcliteralcliteralb"), vec_type({ {e<int>("literal"), e<int>("a")}, {e<int>("literal"), e<int>("c")}, {e<int>("literal"), e<int>("c")}, {e<int>("literal"), e<int>("b")} }), e<int>(""));
		ASSERT_PARSE_SUCCESS(Oom4, e<int>("literalaliteralcliteralcliteralbliteral"), vec_type({ {e<int>("literal"), e<int>("a")}, {e<int>("literal"), e<int>("c")}, {e<int>("literal"), e<int>("c")}, {e<int>("literal"), e<int>("b")} }), e<int>("literal"));
		ASSERT_PARSE_FAILURE(Oom4, e<int>("aliteralaliteralcliteralbliteral"));
		ASSERT_PARSE_FAILURE(Oom4, e<int>(""));
	}
}

TEST("one_or_more_parser", "Parse one_or_more_parser<void-parser>")
{
	using P = one_or_more_parser<ignore_parser<ABC>>;

	ASSERT_PARSE_SUCCESS_VOID(P, "abcabcabca", "a");
	ASSERT_PARSE_SUCCESS_VOID(P, "abcabca", "a");
	ASSERT_PARSE_SUCCESS_VOID(P, "abcabc", "");
	ASSERT_PARSE_FAILURE(P, " abcabc");
	ASSERT_PARSE_SUCCESS_VOID(P, "abcab", "ab");
	ASSERT_PARSE_SUCCESS_VOID(P, "abc", "");
	ASSERT_PARSE_FAILURE(P, "");

	ASSERT_PARSE_SUCCESS_VOID(P, L"abcabcabca", L"a");
	ASSERT_PARSE_SUCCESS_VOID(P, L"abcabca", L"a");
	ASSERT_PARSE_SUCCESS_VOID(P, L"abcabc", L"");
	ASSERT_PARSE_FAILURE(P, L" abcabc");
	ASSERT_PARSE_SUCCESS_VOID(P, L"abcab", L"ab");
	ASSERT_PARSE_SUCCESS_VOID(P, L"abc", L"");
	ASSERT_PARSE_FAILURE(P, L"");

	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabcabca"), e<int>("a"));
	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabca"), e<int>("a"));
	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcabc"), e<int>(""));
	ASSERT_PARSE_FAILURE(P, e<int>(" abcabc"));
	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abcab"), e<int>("ab"));
	ASSERT_PARSE_SUCCESS_VOID(P, e<int>("abc"), e<int>(""));
	ASSERT_PARSE_FAILURE(P, e<int>(""));
}
