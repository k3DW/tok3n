#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

using TwoWay = Seq1;
using ThreeWay = Seq3;

FIXTURE("Sequence");

TEST("Sequence", "Requirements")
{
	ASSERT_IS_PARSER(TwoWay, SequenceFamily, std::tuple<Output<wchar_t>, Output<wchar_t>>);
	ASSERT_IS_PARSER(ThreeWay, SequenceFamily, std::tuple<Output<wchar_t>, Output<wchar_t>, Output<wchar_t>>);
	ASSERT_IS_PARSER(Seq5, SequenceFamily, void);
}

TEST("Sequence", "Parse two-way Sequence")
{
	ASSERT_PARSE_FAILURE(TwoWay, L"abc");
	ASSERT_PARSE_FAILURE(TwoWay, L"abcd");
	ASSERT_PARSE_SUCCESS(TwoWay, L"abef", std::tuple(L"ab", L"e"), L"f");
	ASSERT_PARSE_SUCCESS(TwoWay, L"ab ef", std::tuple(L"ab", L" "), L"ef");
}

TEST("Sequence", "Parse three-way Sequence")
{
	ASSERT_PARSE_SUCCESS(ThreeWay, L"abcde", std::tuple(L"ab", L"c", L"d"), L"e");
	ASSERT_PARSE_SUCCESS(ThreeWay, L"abdc", std::tuple(L"ab", L"d", L"c"), L"");
	ASSERT_PARSE_FAILURE(ThreeWay, L"abcz");
}

TEST("Sequence", "Parse void result_type")
{
	ASSERT_PARSE_FAILURE(Seq5, L"ab");
	ASSERT_PARSE_FAILURE(Seq5, L"abca");
	ASSERT_PARSE_SUCCESS_VOID(Seq5, L"abcabcabcdabcd", L"dabcd");
}



TEST("Sequence", "Not constructible empty")
{
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Sequence);
}



TEST("Sequence", "Sequence<Ignore>")
{
	using P = Sequence<ABC, Ignore<QQ>, ABC>;

	ASSERT_PARSE_SUCCESS(P, L"abc??abc??", std::tuple(L"abc", L"abc"), L"??");
	ASSERT_PARSE_FAILURE(P, L"abcabc??");
}
