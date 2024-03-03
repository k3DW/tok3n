#include "pch.h"
#include "char-samples/char-samples.h"

using TwoWay = Seq1;
using ThreeWay = Seq3;

FIXTURE("Sequence");

TEST("Sequence", "Requirements")
{
	ASSERT_IS_PARSER(TwoWay, SequenceFamily, std::tuple<Output<char>, Output<char>>);
	ASSERT_IS_PARSER(ThreeWay, SequenceFamily, std::tuple<Output<char>, Output<char>, Output<char>>);
	ASSERT_IS_PARSER(Seq5, SequenceFamily, void);
}

TEST("Sequence", "Parse two-way Sequence")
{
	ASSERT_PARSE_FAILURE(TwoWay, "abc");
	ASSERT_PARSE_FAILURE(TwoWay, "abcd");
	ASSERT_PARSE_SUCCESS(TwoWay, "abef", std::tuple("ab", "e"), "f");
	ASSERT_PARSE_SUCCESS(TwoWay, "ab ef", std::tuple("ab", " "), "ef");
}

TEST("Sequence", "Parse three-way Sequence")
{
	ASSERT_PARSE_SUCCESS(ThreeWay, "abcde", std::tuple("ab", "c", "d"), "e");
	ASSERT_PARSE_SUCCESS(ThreeWay, "abdc", std::tuple("ab", "d", "c"), "");
	ASSERT_PARSE_FAILURE(ThreeWay, "abcz");
}

TEST("Sequence", "Parse void result_type")
{
	ASSERT_PARSE_FAILURE(Seq5, "ab");
	ASSERT_PARSE_FAILURE(Seq5, "abca");
	ASSERT_PARSE_SUCCESS_VOID(Seq5, "abcabcabcdabcd", "dabcd");
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
}
