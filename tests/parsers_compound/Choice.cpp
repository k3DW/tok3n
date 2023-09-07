#include "pch.h"

using TwoWay1 = Cho1;
using TwoWay2 = Cho2;

using ThreeWay1 = Cho3;
using ThreeWay2 = Cho4;

FIXTURE("Choice");

TEST("Choice", "Requirements")
{
	ASSERT_IS_PARSER(TwoWay1, ChoiceType, Output);
	ASSERT_IS_PARSER(TwoWay2, ChoiceType, Output);
	ASSERT_IS_PARSER(ThreeWay1, ChoiceType, Output);
	ASSERT_IS_PARSER(ThreeWay2, ChoiceType, Output);
	ASSERT_IS_PARSER(Cho5, ChoiceType, void);
}

TEST("Choice", "Parse two-way Choice")
{
	ASSERT_PARSE_SUCCESS(TwoWay1, "abc", "ab", "c");
	ASSERT_PARSE_SUCCESS(TwoWay1, "ba", "b", "a");
	ASSERT_PARSE_FAILURE(TwoWay1, "cba");
	ASSERT_PARSE_FAILURE(TwoWay1, "dcba");
	ASSERT_PARSE_SUCCESS(TwoWay1, "edcba", "e", "dcba");

	ASSERT_PARSE_SUCCESS(TwoWay2, "abc", "a", "bc");
	ASSERT_PARSE_SUCCESS(TwoWay2, "ba", "b", "a");
	ASSERT_PARSE_FAILURE(TwoWay2, "cba");
	ASSERT_PARSE_FAILURE(TwoWay2, "dcba");
	ASSERT_PARSE_SUCCESS(TwoWay2, "edcba", "e", "dcba");
}

TEST("Choice", "Parse three-way Choice")
{
	ASSERT_PARSE_SUCCESS(ThreeWay1, "abc", "ab", "c");
	ASSERT_PARSE_SUCCESS(ThreeWay1, "ba", "b", "a");
	ASSERT_PARSE_SUCCESS(ThreeWay1, "cba", "c", "ba");
	ASSERT_PARSE_SUCCESS(ThreeWay1, "dcba", "d", "cba");
	ASSERT_PARSE_SUCCESS(ThreeWay1, "edcba", "e", "dcba");

	ASSERT_PARSE_SUCCESS(ThreeWay2, "abc", "a", "bc");
	ASSERT_PARSE_SUCCESS(ThreeWay2, "ba", "b", "a");
	ASSERT_PARSE_SUCCESS(ThreeWay2, "cba", "c", "ba");
	ASSERT_PARSE_SUCCESS(ThreeWay2, "dcba", "d", "cba");
	ASSERT_PARSE_SUCCESS(ThreeWay2, "edcba", "e", "dcba");

	ASSERT_PARSE_FAILURE(ThreeWay1, "zyx");
	ASSERT_PARSE_SUCCESS(ThreeWay1, "xyz", "x", "yz");
	ASSERT_PARSE_FAILURE(ThreeWay2, "zyx");
	ASSERT_PARSE_SUCCESS(ThreeWay2, "xyz", "x", "yz");
}

TEST("Choice", "Parse void result_type")
{
	ASSERT_PARSE_FAILURE(Cho5, "ab");
	ASSERT_PARSE_SUCCESS_VOID(Cho5, "abca", "a");
	ASSERT_PARSE_SUCCESS_VOID(Cho5, "abcabcabc", "abcabc");
}



TEST("Choice", "Constructible only from parsers with the same result_type")
{
	ASSERT_PARSER_CONSTRUCTIBLE(Choice, OC1, OC3, NC2, NC1, L2);
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Choice, OC1, Sequence<OC2, OC3>);
}

TEST("Choice", "Not constructible empty")
{
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Choice);
}



TEST("Choice", "Move only")
{
	using T = MoveOnlyWrapper<Output>;
	using P = Choice<Into<OC3, T>, Into<ABC, T>>;

	ASSERT_PARSE_SUCCESS(P, "xyz", T("x"), "yz");
	ASSERT_PARSE_FAILURE(P, "abxyz");
	ASSERT_PARSE_SUCCESS(P, "abcxyz", T("abc"), "xyz");
	ASSERT_PARSE_SUCCESS(P, "zabcxyz", T("z"), "abcxyz");
}

TEST("Choice", "Copy only")
{
	using T = CopyOnlyWrapper<Output>;
	using P = Choice<Into<OC3, T>, Into<ABC, T>>;

	ASSERT_PARSE_SUCCESS(P, "xyz", T("x"), "yz");
	ASSERT_PARSE_FAILURE(P, "abxyz");
	ASSERT_PARSE_SUCCESS(P, "abcxyz", T("abc"), "xyz");
	ASSERT_PARSE_SUCCESS(P, "zabcxyz", T("z"), "abcxyz");
}
