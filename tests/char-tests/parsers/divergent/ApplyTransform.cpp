#include "samples.h"

FIXTURE("ApplyTransform");

TEST("ApplyTransform", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Apt1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Apt2, value_type);

	ASSERT_IS_PARSER(Apt1, char, ApplyTransformFamily, bool);
	ASSERT_IS_PARSER(Apt2, char, ApplyTransformFamily, std::size_t);

	ASSERT_IS_PARSER(Apt1, wchar_t, ApplyTransformFamily, bool);
	ASSERT_IS_PARSER(Apt2, wchar_t, ApplyTransformFamily, std::size_t);

	ASSERT_IS_PARSER(Apt1, int, ApplyTransformFamily, bool);
	ASSERT_IS_PARSER(Apt2, int, ApplyTransformFamily, std::size_t);
}

TEST("ApplyTransform", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Apt1, "abc???????", false, "?");
	ASSERT_PARSE_FAILURE(Apt1, "??abc???????");
	ASSERT_PARSE_SUCCESS(Apt1, "abc??abc???????", false, "abc???????");
	ASSERT_PARSE_SUCCESS(Apt1, "abc ??abc???????", true, " ??abc???????");
	ASSERT_PARSE_FAILURE(Apt1, "");

	ASSERT_PARSE_SUCCESS(Apt2, "abcabcabcabc??", 36, "");
	ASSERT_PARSE_SUCCESS(Apt2, "abcabcabcabc", 12, "");
	ASSERT_PARSE_SUCCESS(Apt2, "abcabcabcabc ??", 12, " ??");
	ASSERT_PARSE_SUCCESS(Apt2, "abc", 3, "");
	ASSERT_PARSE_FAILURE(Apt2, " abc");
	ASSERT_PARSE_FAILURE(Apt2, "");

	ASSERT_PARSE_SUCCESS(Apt1, L"abc???????", false, L"?");
	ASSERT_PARSE_FAILURE(Apt1, L"??abc???????");
	ASSERT_PARSE_SUCCESS(Apt1, L"abc??abc???????", false, L"abc???????");
	ASSERT_PARSE_SUCCESS(Apt1, L"abc ??abc???????", true, L" ??abc???????");
	ASSERT_PARSE_FAILURE(Apt1, L"");

	ASSERT_PARSE_SUCCESS(Apt2, L"abcabcabcabc??", 36, L"");
	ASSERT_PARSE_SUCCESS(Apt2, L"abcabcabcabc", 12, L"");
	ASSERT_PARSE_SUCCESS(Apt2, L"abcabcabcabc ??", 12, L" ??");
	ASSERT_PARSE_SUCCESS(Apt2, L"abc", 3, L"");
	ASSERT_PARSE_FAILURE(Apt2, L" abc");
	ASSERT_PARSE_FAILURE(Apt2, L"");

	ASSERT_PARSE_SUCCESS(Apt1, e<int>("abc???????"), false, e<int>("?"));
	ASSERT_PARSE_FAILURE(Apt1, e<int>("??abc???????"));
	ASSERT_PARSE_SUCCESS(Apt1, e<int>("abc??abc???????"), false, e<int>("abc???????"));
	ASSERT_PARSE_SUCCESS(Apt1, e<int>("abc ??abc???????"), true, e<int>(" ??abc???????"));
	ASSERT_PARSE_FAILURE(Apt1, e<int>(""));

	ASSERT_PARSE_SUCCESS(Apt2, e<int>("abcabcabcabc??"), 36, e<int>(""));
	ASSERT_PARSE_SUCCESS(Apt2, e<int>("abcabcabcabc"), 12, e<int>(""));
	ASSERT_PARSE_SUCCESS(Apt2, e<int>("abcabcabcabc ??"), 12, e<int>(" ??"));
	ASSERT_PARSE_SUCCESS(Apt2, e<int>("abc"), 3, e<int>(""));
	ASSERT_PARSE_FAILURE(Apt2, e<int>(" abc"));
	ASSERT_PARSE_FAILURE(Apt2, e<int>(""));
}

TEST("ApplyTransform", "Move only")
{
	{
		using tuple = std::tuple<Output<char>, Output<char>>;
		using T = MoveOnlyWrapper<tuple>;
		using P = ApplyTransform<Sequence<Any3, ABC>, Const<T::make>>;
		ASSERT_PARSE_SUCCESS(P, "xabcd", T(std::tuple("x", "abc")), "d");
		ASSERT_PARSE_FAILURE(P, "ydcba");
		ASSERT_PARSE_SUCCESS(P, "zabcabcd", T(std::tuple("z", "abc")), "abcd");
	}

	{
		using tuple = std::tuple<Output<wchar_t>, Output<wchar_t>>;
		using T = MoveOnlyWrapper<tuple>;
		using P = ApplyTransform<Sequence<Any3, ABC>, Const<T::make>>;
		ASSERT_PARSE_SUCCESS(P, L"xabcd", T(std::tuple(L"x", L"abc")), L"d");
		ASSERT_PARSE_FAILURE(P, L"ydcba");
		ASSERT_PARSE_SUCCESS(P, L"zabcabcd", T(std::tuple(L"z", L"abc")), L"abcd");
	}

	{
		using tuple = std::tuple<Output<int>, Output<int>>;
		using T = MoveOnlyWrapper<tuple>;
		using P = ApplyTransform<Sequence<Any3, ABC>, Const<T::make>>;
		ASSERT_PARSE_SUCCESS(P, e<int>("xabcd"), T(std::tuple(e<int>("x"), e<int>("abc"))), e<int>("d"));
		ASSERT_PARSE_FAILURE(P, e<int>("ydcba"));
		ASSERT_PARSE_SUCCESS(P, e<int>("zabcabcd"), T(std::tuple(e<int>("z"), e<int>("abc"))), e<int>("abcd"));
	}
}

TEST("ApplyTransform", "Copy only")
{
	{
		using tuple = std::tuple<Output<char>, Output<char>>;
		using T = CopyOnlyWrapper<tuple>;
		using P = ApplyTransform<Sequence<Any3, ABC>, Const<T::make>>;
		ASSERT_PARSE_SUCCESS(P, "xabcd", T(std::tuple("x", "abc")), "d");
		ASSERT_PARSE_FAILURE(P, "ydcba");
		ASSERT_PARSE_SUCCESS(P, "zabcabcd", T(std::tuple("z", "abc")), "abcd");
	}

	{
		using tuple = std::tuple<Output<wchar_t>, Output<wchar_t>>;
		using T = CopyOnlyWrapper<tuple>;
		using P = ApplyTransform<Sequence<Any3, ABC>, Const<T::make>>;
		ASSERT_PARSE_SUCCESS(P, L"xabcd", T(std::tuple(L"x", L"abc")), L"d");
		ASSERT_PARSE_FAILURE(P, L"ydcba");
		ASSERT_PARSE_SUCCESS(P, L"zabcabcd", T(std::tuple(L"z", L"abc")), L"abcd");
	}

	{
		using tuple = std::tuple<Output<int>, Output<int>>;
		using T = CopyOnlyWrapper<tuple>;
		using P = ApplyTransform<Sequence<Any3, ABC>, Const<T::make>>;
		ASSERT_PARSE_SUCCESS(P, e<int>("xabcd"), T(std::tuple(e<int>("x"), e<int>("abc"))), e<int>("d"));
		ASSERT_PARSE_FAILURE(P, e<int>("ydcba"));
		ASSERT_PARSE_SUCCESS(P, e<int>("zabcabcd"), T(std::tuple(e<int>("z"), e<int>("abc"))), e<int>("abcd"));
	}
}
