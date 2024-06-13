#include "pch.h"
#include "char-tests/samples.h"

using TwoWay = Seq1;
using ThreeWay = Seq3;

FIXTURE("Sequence");

TEST("Sequence", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(TwoWay, value_type);
	ASSERT_PARSER_VALUE_TYPE(ThreeWay, value_type);
	ASSERT_PARSER_VALUE_TYPE(Seq5, value_type);

	ASSERT_IS_PARSER(TwoWay, char, SequenceFamily, std::tuple<Output<char>, Output<char>>);
	ASSERT_IS_PARSER(ThreeWay, char, SequenceFamily, std::tuple<Output<char>, Output<char>, Output<char>>);
	ASSERT_IS_PARSER(Seq5, char, SequenceFamily, void);

	ASSERT_IS_PARSER(TwoWay, wchar_t, SequenceFamily, std::tuple<Output<wchar_t>, Output<wchar_t>>);
	ASSERT_IS_PARSER(ThreeWay, wchar_t, SequenceFamily, std::tuple<Output<wchar_t>, Output<wchar_t>, Output<wchar_t>>);
	ASSERT_IS_PARSER(Seq5, wchar_t, SequenceFamily, void);

	ASSERT_IS_PARSER(TwoWay, int, SequenceFamily, std::tuple<Output<int>, Output<int>>);
	ASSERT_IS_PARSER(ThreeWay, int, SequenceFamily, std::tuple<Output<int>, Output<int>, Output<int>>);
	ASSERT_IS_PARSER(Seq5, int, SequenceFamily, void);
}

TEST("Sequence", "Parse two-way Sequence")
{
	ASSERT_PARSE_FAILURE(TwoWay, "abc");
	ASSERT_PARSE_FAILURE(TwoWay, "abcd");
	ASSERT_PARSE_SUCCESS(TwoWay, "abef", std::tuple("ab", "e"), "f");
	ASSERT_PARSE_SUCCESS(TwoWay, "ab ef", std::tuple("ab", " "), "ef");

	ASSERT_PARSE_FAILURE(TwoWay, L"abc");
	ASSERT_PARSE_FAILURE(TwoWay, L"abcd");
	ASSERT_PARSE_SUCCESS(TwoWay, L"abef", std::tuple(L"ab", L"e"), L"f");
	ASSERT_PARSE_SUCCESS(TwoWay, L"ab ef", std::tuple(L"ab", L" "), L"ef");

	ASSERT_PARSE_FAILURE(TwoWay, e<int>("abc"));
	ASSERT_PARSE_FAILURE(TwoWay, e<int>("abcd"));
	ASSERT_PARSE_SUCCESS(TwoWay, e<int>("abef"), std::tuple(e<int>("ab"), e<int>("e")), e<int>("f"));
	ASSERT_PARSE_SUCCESS(TwoWay, e<int>("ab ef"), std::tuple(e<int>("ab"), e<int>(" ")), e<int>("ef"));
}

TEST("Sequence", "Parse three-way Sequence")
{
	ASSERT_PARSE_SUCCESS(ThreeWay, "abcde", std::tuple("ab", "c", "d"), "e");
	ASSERT_PARSE_SUCCESS(ThreeWay, "abdc", std::tuple("ab", "d", "c"), "");
	ASSERT_PARSE_FAILURE(ThreeWay, "abcz");

	ASSERT_PARSE_SUCCESS(ThreeWay, L"abcde", std::tuple(L"ab", L"c", L"d"), L"e");
	ASSERT_PARSE_SUCCESS(ThreeWay, L"abdc", std::tuple(L"ab", L"d", L"c"), L"");
	ASSERT_PARSE_FAILURE(ThreeWay, L"abcz");

	ASSERT_PARSE_SUCCESS(ThreeWay, e<int>("abcde"), std::tuple(e<int>("ab"), e<int>("c"), e<int>("d")), e<int>("e"));
	ASSERT_PARSE_SUCCESS(ThreeWay, e<int>("abdc"), std::tuple(e<int>("ab"), e<int>("d"), e<int>("c")), e<int>());
	ASSERT_PARSE_FAILURE(ThreeWay, e<int>("abcz"));
}

TEST("Sequence", "Parse void result_type")
{
	ASSERT_PARSE_FAILURE(Seq5, "ab");
	ASSERT_PARSE_FAILURE(Seq5, "abca");
	ASSERT_PARSE_SUCCESS_VOID(Seq5, "abcabcabcdabcd", "dabcd");

	ASSERT_PARSE_FAILURE(Seq5, L"ab");
	ASSERT_PARSE_FAILURE(Seq5, L"abca");
	ASSERT_PARSE_SUCCESS_VOID(Seq5, L"abcabcabcdabcd", L"dabcd");

	ASSERT_PARSE_FAILURE(Seq5, e<int>("ab"));
	ASSERT_PARSE_FAILURE(Seq5, e<int>("abca"));
	ASSERT_PARSE_SUCCESS_VOID(Seq5, e<int>("abcabcabcdabcd"), e<int>("dabcd"));
}



TEST("Sequence", "Not constructible empty")
{
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Sequence);
}



TEST("Sequence", "Sequence<Ignore>")
{
	using P = Sequence<ABC, Ignore<QQ>, ABC>;

	ASSERT_PARSE_SUCCESS(P, "abc??abc??", std::tuple("abc", "abc"), "??");
	ASSERT_PARSE_FAILURE(P, "abcabc??");

	ASSERT_PARSE_SUCCESS(P, L"abc??abc??", std::tuple(L"abc", L"abc"), L"??");
	ASSERT_PARSE_FAILURE(P, L"abcabc??");

	ASSERT_PARSE_SUCCESS(P, e<int>("abc??abc??"), std::tuple(e<int>("abc"), e<int>("abc")), e<int>("??"));
	ASSERT_PARSE_FAILURE(P, e<int>("abcabc??"));
}
