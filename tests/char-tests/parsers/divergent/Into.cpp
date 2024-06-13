#include "pch.h"
#include "char-tests/samples.h"

FIXTURE("Into");

TEST("Into", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Int1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Int2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Int3, value_type);

	ASSERT_IS_PARSER(Int1, char, IntoFamily, Class1);
	ASSERT_IS_PARSER(Int2, char, IntoFamily, Class2);
	ASSERT_IS_PARSER(Int3, char, IntoFamily, Class2);

	ASSERT_IS_PARSER(Int1, wchar_t, IntoFamily, Class1);
	ASSERT_IS_PARSER(Int2, wchar_t, IntoFamily, Class2);
	ASSERT_IS_PARSER(Int3, wchar_t, IntoFamily, Class2);

	ASSERT_IS_PARSER(Int1, int, IntoFamily, Class1);
	ASSERT_IS_PARSER(Int2, int, IntoFamily, Class2);
	ASSERT_IS_PARSER(Int3, int, IntoFamily, Class2);
}

TEST("Into", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Int1, " ", Class1(0), "");
	ASSERT_PARSE_FAILURE(Int1, "a");
	ASSERT_PARSE_SUCCESS(Int1, ".", Class1(1), "");
	ASSERT_PARSE_FAILURE(Int1, "");

	ASSERT_PARSE_SUCCESS(Int2, "abc.", Class2("abc", "."), "");
	ASSERT_PARSE_SUCCESS(Int2, "abc . ", Class2("abc", " "), ". ");
	ASSERT_PARSE_FAILURE(Int2, "");
	ASSERT_PARSE_FAILURE(Int2, "abc");

	ASSERT_PARSE_SUCCESS(Int3, "abc.", Class2("abc", "."), "");
	ASSERT_PARSE_SUCCESS(Int3, "abc . ", Class2("abc", " "), ". ");
	ASSERT_PARSE_FAILURE(Int3, "");
	ASSERT_PARSE_FAILURE(Int3, "abc");

	ASSERT_PARSE_SUCCESS(Int1, L" ", Class1(0), L"");
	ASSERT_PARSE_FAILURE(Int1, L"a");
	ASSERT_PARSE_SUCCESS(Int1, L".", Class1(1), L"");
	ASSERT_PARSE_FAILURE(Int1, L"");

	ASSERT_PARSE_SUCCESS(Int2, L"abc.", Class2(L"abc", L"."), L"");
	ASSERT_PARSE_SUCCESS(Int2, L"abc . ", Class2(L"abc", L" "), L". ");
	ASSERT_PARSE_FAILURE(Int2, L"");
	ASSERT_PARSE_FAILURE(Int2, L"abc");

	ASSERT_PARSE_SUCCESS(Int3, L"abc.", Class2(L"abc", L"."), L"");
	ASSERT_PARSE_SUCCESS(Int3, L"abc . ", Class2(L"abc", L" "), L". ");
	ASSERT_PARSE_FAILURE(Int3, L"");
	ASSERT_PARSE_FAILURE(Int3, L"abc");

	ASSERT_PARSE_SUCCESS(Int1, e<int>(" "), Class1(0), e<int>(""));
	ASSERT_PARSE_FAILURE(Int1, e<int>("a"));
	ASSERT_PARSE_SUCCESS(Int1, e<int>("."), Class1(1), e<int>(""));
	ASSERT_PARSE_FAILURE(Int1, e<int>(""));

	ASSERT_PARSE_SUCCESS(Int2, e<int>("abc."), Class2(e<int>("abc"), e<int>(".")), e<int>(""));
	ASSERT_PARSE_SUCCESS(Int2, e<int>("abc . "), Class2(e<int>("abc"), e<int>(" ")), e<int>(". "));
	ASSERT_PARSE_FAILURE(Int2, e<int>(""));
	ASSERT_PARSE_FAILURE(Int2, e<int>("abc"));

	ASSERT_PARSE_SUCCESS(Int3, e<int>("abc."), Class2(e<int>("abc"), e<int>(".")), e<int>(""));
	ASSERT_PARSE_SUCCESS(Int3, e<int>("abc . "), Class2(e<int>("abc"), e<int>(" ")), e<int>(". "));
	ASSERT_PARSE_FAILURE(Int3, e<int>(""));
	ASSERT_PARSE_FAILURE(Int3, e<int>("abc"));
}

TEST("Into", "Move only")
{
	{
		using T = MoveOnlyWrapper<Output<char>>;
		using P = Into<ABC, T>;
		ASSERT_PARSE_SUCCESS(P, "abcd", T("abc"), "d");
		ASSERT_PARSE_FAILURE(P, "dcba");
		ASSERT_PARSE_SUCCESS(P, "abcabcd", T("abc"), "abcd");
	}

	{
		using T = MoveOnlyWrapper<Output<wchar_t>>;
		using P = Into<ABC, T>;
		ASSERT_PARSE_SUCCESS(P, L"abcd", T(L"abc"), L"d");
		ASSERT_PARSE_FAILURE(P, L"dcba");
		ASSERT_PARSE_SUCCESS(P, L"abcabcd", T(L"abc"), L"abcd");
	}

	{
		using T = MoveOnlyWrapper<Output<int>>;
		using P = Into<ABC, T>;
		ASSERT_PARSE_SUCCESS(P, e<int>("abcd"), T(e<int>("abc")), e<int>("d"));
		ASSERT_PARSE_FAILURE(P, e<int>("dcba"));
		ASSERT_PARSE_SUCCESS(P, e<int>("abcabcd"), T(e<int>("abc")), e<int>("abcd"));
	}
}

TEST("Into", "Copy only")
{
	{
		using T = CopyOnlyWrapper<Output<char>>;
		using P = Into<ABC, T>;
		ASSERT_PARSE_SUCCESS(P, "abcd", T("abc"), "d");
		ASSERT_PARSE_FAILURE(P, "dcba");
		ASSERT_PARSE_SUCCESS(P, "abcabcd", T("abc"), "abcd");
	}

	{
		using T = CopyOnlyWrapper<Output<wchar_t>>;
		using P = Into<ABC, T>;
		ASSERT_PARSE_SUCCESS(P, L"abcd", T(L"abc"), L"d");
		ASSERT_PARSE_FAILURE(P, L"dcba");
		ASSERT_PARSE_SUCCESS(P, L"abcabcd", T(L"abc"), L"abcd");
	}

	{
		using T = CopyOnlyWrapper<Output<int>>;
		using P = Into<ABC, T>;
		ASSERT_PARSE_SUCCESS(P, e<int>("abcd"), T(e<int>("abc")), e<int>("d"));
		ASSERT_PARSE_FAILURE(P, e<int>("dcba"));
		ASSERT_PARSE_SUCCESS(P, e<int>("abcabcd"), T(e<int>("abc")), e<int>("abcd"));
	}
}
