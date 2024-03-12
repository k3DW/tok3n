#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

using TwoWay1 = Cho1;
using TwoWay2 = Cho2;

using ThreeWay1 = Cho3;
using ThreeWay2 = Cho4;

FIXTURE("Choice");

TEST("Choice", "Requirements")
{
	ASSERT_IS_PARSER(TwoWay1, wchar_t, ChoiceFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(TwoWay2, wchar_t, ChoiceFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(ThreeWay1, wchar_t, ChoiceFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(ThreeWay2, wchar_t, ChoiceFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Cho5, wchar_t, ChoiceFamily, void);
}

TEST("Choice", "Parse two-way Choice")
{
	ASSERT_PARSE_SUCCESS(TwoWay1, L"abc", L"ab", L"c");
	ASSERT_PARSE_SUCCESS(TwoWay1, L"ba", L"b", L"a");
	ASSERT_PARSE_FAILURE(TwoWay1, L"cba");
	ASSERT_PARSE_FAILURE(TwoWay1, L"dcba");
	ASSERT_PARSE_SUCCESS(TwoWay1, L"edcba", L"e", L"dcba");

	ASSERT_PARSE_SUCCESS(TwoWay2, L"abc", L"a", L"bc");
	ASSERT_PARSE_SUCCESS(TwoWay2, L"ba", L"b", L"a");
	ASSERT_PARSE_FAILURE(TwoWay2, L"cba");
	ASSERT_PARSE_FAILURE(TwoWay2, L"dcba");
	ASSERT_PARSE_SUCCESS(TwoWay2, L"edcba", L"e", L"dcba");
}

TEST("Choice", "Parse three-way Choice")
{
	ASSERT_PARSE_SUCCESS(ThreeWay1, L"abc", L"ab", L"c");
	ASSERT_PARSE_SUCCESS(ThreeWay1, L"ba", L"b", L"a");
	ASSERT_PARSE_SUCCESS(ThreeWay1, L"cba", L"c", L"ba");
	ASSERT_PARSE_SUCCESS(ThreeWay1, L"dcba", L"d", L"cba");
	ASSERT_PARSE_SUCCESS(ThreeWay1, L"edcba", L"e", L"dcba");

	ASSERT_PARSE_SUCCESS(ThreeWay2, L"abc", L"a", L"bc");
	ASSERT_PARSE_SUCCESS(ThreeWay2, L"ba", L"b", L"a");
	ASSERT_PARSE_SUCCESS(ThreeWay2, L"cba", L"c", L"ba");
	ASSERT_PARSE_SUCCESS(ThreeWay2, L"dcba", L"d", L"cba");
	ASSERT_PARSE_SUCCESS(ThreeWay2, L"edcba", L"e", L"dcba");

	ASSERT_PARSE_FAILURE(ThreeWay1, L"zyx");
	ASSERT_PARSE_SUCCESS(ThreeWay1, L"xyz", L"x", L"yz");
	ASSERT_PARSE_FAILURE(ThreeWay2, L"zyx");
	ASSERT_PARSE_SUCCESS(ThreeWay2, L"xyz", L"x", L"yz");
}

TEST("Choice", "Parse void result_type")
{
	ASSERT_PARSE_FAILURE(Cho5, L"ab");
	ASSERT_PARSE_SUCCESS_VOID(Cho5, L"abca", L"a");
	ASSERT_PARSE_SUCCESS_VOID(Cho5, L"abcabcabc", L"abcabc");
}



TEST("Choice", "Constructible not only from parsers with the same result_type")
{
	ASSERT_PARSER_CONSTRUCTIBLE(Choice, Any1, Any3, Non2, Non1, All2);
	ASSERT_PARSER_CONSTRUCTIBLE(Choice, Any1, Sequence<Any2, Any3>);
}

TEST("Choice", "Not constructible empty")
{
	ASSERT_PARSER_NOT_CONSTRUCTIBLE(Choice);
}



TEST("Choice", "Move only")
{
	using T = MoveOnlyWrapper<Output<wchar_t>>;
	using P = Choice<Into<Any3, T>, Into<ABC, T>>;

	ASSERT_PARSE_SUCCESS(P, L"xyz", T(L"x"), L"yz");
	ASSERT_PARSE_FAILURE(P, L"abxyz");
	ASSERT_PARSE_SUCCESS(P, L"abcxyz", T(L"abc"), L"xyz");
	ASSERT_PARSE_SUCCESS(P, L"zabcxyz", T(L"z"), L"abcxyz");
}

TEST("Choice", "Copy only")
{
	using T = CopyOnlyWrapper<Output<wchar_t>>;
	using P = Choice<Into<Any3, T>, Into<ABC, T>>;

	ASSERT_PARSE_SUCCESS(P, L"xyz", T(L"x"), L"yz");
	ASSERT_PARSE_FAILURE(P, L"abxyz");
	ASSERT_PARSE_SUCCESS(P, L"abcxyz", T(L"abc"), L"xyz");
	ASSERT_PARSE_SUCCESS(P, L"zabcxyz", T(L"z"), L"abcxyz");
}
