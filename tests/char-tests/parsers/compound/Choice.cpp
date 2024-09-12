#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

using TwoWay1 = Cho1;
using TwoWay2 = Cho2;

using ThreeWay1 = Cho3;
using ThreeWay2 = Cho4;

FIXTURE("Choice");

TEST("Choice", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(TwoWay1, value_type);
	ASSERT_PARSER_VALUE_TYPE(TwoWay2, value_type);
	ASSERT_PARSER_VALUE_TYPE(ThreeWay1, value_type);
	ASSERT_PARSER_VALUE_TYPE(ThreeWay2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Cho5, value_type);

	ASSERT_IS_PARSER(TwoWay1, char, choice_family, output_span<char>);
	ASSERT_IS_PARSER(TwoWay2, char, choice_family, output_span<char>);
	ASSERT_IS_PARSER(ThreeWay1, char, choice_family, output_span<char>);
	ASSERT_IS_PARSER(ThreeWay2, char, choice_family, output_span<char>);
	ASSERT_IS_PARSER(Cho5, char, choice_family, void);

	ASSERT_IS_PARSER(TwoWay1, wchar_t, choice_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(TwoWay2, wchar_t, choice_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(ThreeWay1, wchar_t, choice_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(ThreeWay2, wchar_t, choice_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(Cho5, wchar_t, choice_family, void);

	ASSERT_IS_PARSER(TwoWay1, int, choice_family, output_span<int>);
	ASSERT_IS_PARSER(TwoWay2, int, choice_family, output_span<int>);
	ASSERT_IS_PARSER(ThreeWay1, int, choice_family, output_span<int>);
	ASSERT_IS_PARSER(ThreeWay2, int, choice_family, output_span<int>);
	ASSERT_IS_PARSER(Cho5, int, choice_family, void);
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

	ASSERT_PARSE_SUCCESS(TwoWay1, e<int>("abc"), e<int>("ab"), e<int>("c"));
	ASSERT_PARSE_SUCCESS(TwoWay1, e<int>("ba"), e<int>("b"), e<int>("a"));
	ASSERT_PARSE_FAILURE(TwoWay1, e<int>("cba"));
	ASSERT_PARSE_FAILURE(TwoWay1, e<int>("dcba"));
	ASSERT_PARSE_SUCCESS(TwoWay1, e<int>("edcba"), e<int>("e"), e<int>("dcba"));

	ASSERT_PARSE_SUCCESS(TwoWay2, e<int>("abc"), e<int>("a"), e<int>("bc"));
	ASSERT_PARSE_SUCCESS(TwoWay2, e<int>("ba"), e<int>("b"), e<int>("a"));
	ASSERT_PARSE_FAILURE(TwoWay2, e<int>("cba"));
	ASSERT_PARSE_FAILURE(TwoWay2, e<int>("dcba"));
	ASSERT_PARSE_SUCCESS(TwoWay2, e<int>("edcba"), e<int>("e"), e<int>("dcba"));
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

	ASSERT_PARSE_SUCCESS(ThreeWay1, e<int>("abc"), e<int>("ab"), e<int>("c"));
	ASSERT_PARSE_SUCCESS(ThreeWay1, e<int>("ba"), e<int>("b"), e<int>("a"));
	ASSERT_PARSE_SUCCESS(ThreeWay1, e<int>("cba"), e<int>("c"), e<int>("ba"));
	ASSERT_PARSE_SUCCESS(ThreeWay1, e<int>("dcba"), e<int>("d"), e<int>("cba"));
	ASSERT_PARSE_SUCCESS(ThreeWay1, e<int>("edcba"), e<int>("e"), e<int>("dcba"));

	ASSERT_PARSE_SUCCESS(ThreeWay2, e<int>("abc"), e<int>("a"), e<int>("bc"));
	ASSERT_PARSE_SUCCESS(ThreeWay2, e<int>("ba"), e<int>("b"), e<int>("a"));
	ASSERT_PARSE_SUCCESS(ThreeWay2, e<int>("cba"), e<int>("c"), e<int>("ba"));
	ASSERT_PARSE_SUCCESS(ThreeWay2, e<int>("dcba"), e<int>("d"), e<int>("cba"));
	ASSERT_PARSE_SUCCESS(ThreeWay2, e<int>("edcba"), e<int>("e"), e<int>("dcba"));

	ASSERT_PARSE_FAILURE(ThreeWay1, e<int>("zyx"));
	ASSERT_PARSE_SUCCESS(ThreeWay1, e<int>("xyz"), e<int>("x"), e<int>("yz"));
	ASSERT_PARSE_FAILURE(ThreeWay2, e<int>("zyx"));
	ASSERT_PARSE_SUCCESS(ThreeWay2, e<int>("xyz"), e<int>("x"), e<int>("yz"));
}

TEST("Choice", "Parse void result_type")
{
	ASSERT_PARSE_FAILURE(Cho5, "ab");
	ASSERT_PARSE_SUCCESS_VOID(Cho5, "abca", "a");
	ASSERT_PARSE_SUCCESS_VOID(Cho5, "abcabcabc", "abcabc");

	ASSERT_PARSE_FAILURE(Cho5, L"ab");
	ASSERT_PARSE_SUCCESS_VOID(Cho5, L"abca", L"a");
	ASSERT_PARSE_SUCCESS_VOID(Cho5, L"abcabcabc", L"abcabc");

	ASSERT_PARSE_FAILURE(Cho5, e<int>("ab"));
	ASSERT_PARSE_SUCCESS_VOID(Cho5, e<int>("abca"), e<int>("a"));
	ASSERT_PARSE_SUCCESS_VOID(Cho5, e<int>("abcabcabc"), e<int>("abcabc"));
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
	{
		using T = MoveOnlyWrapper<output_span<char>>;
		using P = Choice<aliases::Into<Any3, T>, aliases::Into<ABC, T>>;
		ASSERT_PARSE_SUCCESS(P, "xyz", T("x"), "yz");
		ASSERT_PARSE_FAILURE(P, "abxyz");
		ASSERT_PARSE_SUCCESS(P, "abcxyz", T("abc"), "xyz");
		ASSERT_PARSE_SUCCESS(P, "zabcxyz", T("z"), "abcxyz");
	}

	{
		using T = MoveOnlyWrapper<output_span<wchar_t>>;
		using P = Choice<aliases::Into<Any3, T>, aliases::Into<ABC, T>>;
		ASSERT_PARSE_SUCCESS(P, L"xyz", T(L"x"), L"yz");
		ASSERT_PARSE_FAILURE(P, L"abxyz");
		ASSERT_PARSE_SUCCESS(P, L"abcxyz", T(L"abc"), L"xyz");
		ASSERT_PARSE_SUCCESS(P, L"zabcxyz", T(L"z"), L"abcxyz");
	}

	{
		using T = MoveOnlyWrapper<output_span<int>>;
		using P = Choice<aliases::Into<Any3, T>, aliases::Into<ABC, T>>;
		ASSERT_PARSE_SUCCESS(P, e<int>("xyz"), T(e<int>("x")), e<int>("yz"));
		ASSERT_PARSE_FAILURE(P, e<int>("abxyz"));
		ASSERT_PARSE_SUCCESS(P, e<int>("abcxyz"), T(e<int>("abc")), e<int>("xyz"));
		ASSERT_PARSE_SUCCESS(P, e<int>("zabcxyz"), T(e<int>("z")), e<int>("abcxyz"));
	}
}

TEST("Choice", "Copy only")
{
	{
		using T = CopyOnlyWrapper<output_span<char>>;
		using P = Choice<aliases::Into<Any3, T>, aliases::Into<ABC, T>>;
		ASSERT_PARSE_SUCCESS(P, "xyz", T("x"), "yz");
		ASSERT_PARSE_FAILURE(P, "abxyz");
		ASSERT_PARSE_SUCCESS(P, "abcxyz", T("abc"), "xyz");
		ASSERT_PARSE_SUCCESS(P, "zabcxyz", T("z"), "abcxyz");
	}

	{
		using T = CopyOnlyWrapper<output_span<wchar_t>>;
		using P = Choice<aliases::Into<Any3, T>, aliases::Into<ABC, T>>;
		ASSERT_PARSE_SUCCESS(P, L"xyz", T(L"x"), L"yz");
		ASSERT_PARSE_FAILURE(P, L"abxyz");
		ASSERT_PARSE_SUCCESS(P, L"abcxyz", T(L"abc"), L"xyz");
		ASSERT_PARSE_SUCCESS(P, L"zabcxyz", T(L"z"), L"abcxyz");
	}

	{
		using T = CopyOnlyWrapper<output_span<int>>;
		using P = Choice<aliases::Into<Any3, T>, aliases::Into<ABC, T>>;
		ASSERT_PARSE_SUCCESS(P, e<int>("xyz"), T(e<int>("x")), e<int>("yz"));
		ASSERT_PARSE_FAILURE(P, e<int>("abxyz"));
		ASSERT_PARSE_SUCCESS(P, e<int>("abcxyz"), T(e<int>("abc")), e<int>("xyz"));
		ASSERT_PARSE_SUCCESS(P, e<int>("zabcxyz"), T(e<int>("z")), e<int>("abcxyz"));
	}
}

TEST("Choice", "Result type")
{
	using C1 = aliases::Constant<SpaceDot, integral_constant<0>>;
	using C2 = aliases::Constant<SpaceDot, integral_constant<1>>;

	using P1 = Choice<ABC, QQ, SpaceDot>;
	ASSERT_IS_PARSER(P1, char, choice_family, output_span<char>);
	ASSERT_IS_PARSER(P1, wchar_t, choice_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(P1, int, choice_family, output_span<int>);

	using P2 = Choice<ABC, C1, QQ>;
	ASSERT_IS_PARSER(P2, char, choice_family, std::variant<output_span<char>, int>);
	ASSERT_IS_PARSER(P2, wchar_t, choice_family, std::variant<output_span<wchar_t>, int>);
	ASSERT_IS_PARSER(P2, int, choice_family, std::variant<output_span<int>, int>);

	using P3 = Choice<ABC, QQ, C1>;
	ASSERT_IS_PARSER(P3, char, choice_family, std::variant<output_span<char>, int>);
	ASSERT_IS_PARSER(P3, wchar_t, choice_family, std::variant<output_span<wchar_t>, int>);
	ASSERT_IS_PARSER(P3, int, choice_family, std::variant<output_span<int>, int>);

	using P4 = Choice<C1, ABC, QQ>;
	ASSERT_IS_PARSER(P4, char, choice_family, std::variant<int, output_span<char>>);
	ASSERT_IS_PARSER(P4, wchar_t, choice_family, std::variant<int, output_span<wchar_t>>);
	ASSERT_IS_PARSER(P4, int, choice_family, std::variant<int, output_span<int>>);

	using P5 = Choice<C1, ABC, QQ, C2>;
	ASSERT_IS_PARSER(P5, char, choice_family, std::variant<int, output_span<char>>);
	ASSERT_IS_PARSER(P5, wchar_t, choice_family, std::variant<int, output_span<wchar_t>>);
	ASSERT_IS_PARSER(P5, int, choice_family, std::variant<int, output_span<int>>);

	using P6 = Choice<C1, ABC, C2, QQ>;
	ASSERT_IS_PARSER(P6, char, choice_family, std::variant<int, output_span<char>>);
	ASSERT_IS_PARSER(P6, wchar_t, choice_family, std::variant<int, output_span<wchar_t>>);
	ASSERT_IS_PARSER(P6, int, choice_family, std::variant<int, output_span<int>>);
}
