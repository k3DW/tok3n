#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("Join");

TEST("Join", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Joi1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Joi2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Joi3, value_type);
	ASSERT_PARSER_VALUE_TYPE(Joi4, value_type);
	ASSERT_PARSER_VALUE_TYPE(Joi5, value_type);

	ASSERT_IS_PARSER(Joi1, char, join_family, output_span<char>);
	ASSERT_IS_PARSER(Joi2, char, join_family, output_span<char>);
	ASSERT_IS_PARSER(Joi3, char, join_family, output_span<char>);
	ASSERT_IS_PARSER(Joi4, char, join_family, output_span<char>);
	ASSERT_IS_PARSER(Joi5, char, join_family, output_span<char>);

	ASSERT_IS_PARSER(Joi1, wchar_t, join_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(Joi2, wchar_t, join_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(Joi3, wchar_t, join_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(Joi4, wchar_t, join_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(Joi5, wchar_t, join_family, output_span<wchar_t>);

	ASSERT_IS_PARSER(Joi1, int, join_family, output_span<int>);
	ASSERT_IS_PARSER(Joi2, int, join_family, output_span<int>);
	ASSERT_IS_PARSER(Joi3, int, join_family, output_span<int>);
	ASSERT_IS_PARSER(Joi4, int, join_family, output_span<int>);
	ASSERT_IS_PARSER(Joi5, int, join_family, output_span<int>);
}

TEST("Join", "Parse all")
{
	ASSERT_PARSE_SUCCESS(Joi1, "abcabc", "abc", "abc");
	ASSERT_PARSE_FAILURE(Joi1, "Abcabc");
	ASSERT_PARSE_FAILURE(Joi1, " abcabc");

	ASSERT_PARSE_SUCCESS(Joi2, "abcabcabcab", "abcabcabc", "ab");
	ASSERT_PARSE_FAILURE(Joi2, "");
	ASSERT_PARSE_FAILURE(Joi2, "ab");
	ASSERT_PARSE_SUCCESS(Joi2, "abc", "abc", "");

	ASSERT_PARSE_SUCCESS(Joi3, "abcabc", "abc", "abc");
	ASSERT_PARSE_SUCCESS(Joi3, "a??bcabc", "", "a??bcabc");
	ASSERT_PARSE_SUCCESS(Joi3, "", "", "");
	ASSERT_PARSE_SUCCESS(Joi3, "??abcabc", "??", "abcabc");
	ASSERT_PARSE_SUCCESS(Joi3, " ??abcabc", "", " ??abcabc");

	ASSERT_PARSE_SUCCESS(Joi4, "abc???????", "abc??????", "?");
	ASSERT_PARSE_FAILURE(Joi4, "??abc???????");
	ASSERT_PARSE_SUCCESS(Joi4, "abc??abc???????", "abc??", "abc???????");
	ASSERT_PARSE_SUCCESS(Joi4, "abc ??abc???????", "abc", " ??abc???????");
	ASSERT_PARSE_FAILURE(Joi4, "");

	ASSERT_PARSE_SUCCESS(Joi5, "abcabcabcabc??", "abcabcabcabc??", "");
	ASSERT_PARSE_SUCCESS(Joi5, "abcabcabcabc", "abcabcabcabc", "");
	ASSERT_PARSE_SUCCESS(Joi5, "abcabcabcabc ??", "abcabcabcabc", " ??");
	ASSERT_PARSE_SUCCESS(Joi5, "abc", "abc", "");
	ASSERT_PARSE_FAILURE(Joi5, " abc");
	ASSERT_PARSE_FAILURE(Joi5, "");

	ASSERT_PARSE_SUCCESS(Joi1, L"abcabc", L"abc", L"abc");
	ASSERT_PARSE_FAILURE(Joi1, L"Abcabc");
	ASSERT_PARSE_FAILURE(Joi1, L" abcabc");

	ASSERT_PARSE_SUCCESS(Joi2, L"abcabcabcab", L"abcabcabc", L"ab");
	ASSERT_PARSE_FAILURE(Joi2, L"");
	ASSERT_PARSE_FAILURE(Joi2, L"ab");
	ASSERT_PARSE_SUCCESS(Joi2, L"abc", L"abc", L"");

	ASSERT_PARSE_SUCCESS(Joi3, L"abcabc", L"abc", L"abc");
	ASSERT_PARSE_SUCCESS(Joi3, L"a??bcabc", L"", L"a??bcabc");
	ASSERT_PARSE_SUCCESS(Joi3, L"", L"", L"");
	ASSERT_PARSE_SUCCESS(Joi3, L"??abcabc", L"??", L"abcabc");
	ASSERT_PARSE_SUCCESS(Joi3, L" ??abcabc", L"", L" ??abcabc");

	ASSERT_PARSE_SUCCESS(Joi4, L"abc???????", L"abc??????", L"?");
	ASSERT_PARSE_FAILURE(Joi4, L"??abc???????");
	ASSERT_PARSE_SUCCESS(Joi4, L"abc??abc???????", L"abc??", L"abc???????");
	ASSERT_PARSE_SUCCESS(Joi4, L"abc ??abc???????", L"abc", L" ??abc???????");
	ASSERT_PARSE_FAILURE(Joi4, L"");

	ASSERT_PARSE_SUCCESS(Joi5, L"abcabcabcabc??", L"abcabcabcabc??", L"");
	ASSERT_PARSE_SUCCESS(Joi5, L"abcabcabcabc", L"abcabcabcabc", L"");
	ASSERT_PARSE_SUCCESS(Joi5, L"abcabcabcabc ??", L"abcabcabcabc", L" ??");
	ASSERT_PARSE_SUCCESS(Joi5, L"abc", L"abc", L"");
	ASSERT_PARSE_FAILURE(Joi5, L" abc");
	ASSERT_PARSE_FAILURE(Joi5, L"");

	ASSERT_PARSE_SUCCESS(Joi1, e<int>("abcabc"), e<int>("abc"), e<int>("abc"));
	ASSERT_PARSE_FAILURE(Joi1, e<int>("Abcabc"));
	ASSERT_PARSE_FAILURE(Joi1, e<int>(" abcabc"));

	ASSERT_PARSE_SUCCESS(Joi2, e<int>("abcabcabcab"), e<int>("abcabcabc"), e<int>("ab"));
	ASSERT_PARSE_FAILURE(Joi2, e<int>(""));
	ASSERT_PARSE_FAILURE(Joi2, e<int>("ab"));
	ASSERT_PARSE_SUCCESS(Joi2, e<int>("abc"), e<int>("abc"), e<int>(""));

	ASSERT_PARSE_SUCCESS(Joi3, e<int>("abcabc"), e<int>("abc"), e<int>("abc"));
	ASSERT_PARSE_SUCCESS(Joi3, e<int>("a??bcabc"), e<int>(""), e<int>("a??bcabc"));
	ASSERT_PARSE_SUCCESS(Joi3, e<int>(""), e<int>(""), e<int>(""));
	ASSERT_PARSE_SUCCESS(Joi3, e<int>("??abcabc"), e<int>("??"), e<int>("abcabc"));
	ASSERT_PARSE_SUCCESS(Joi3, e<int>(" ??abcabc"), e<int>(""), e<int>(" ??abcabc"));

	ASSERT_PARSE_SUCCESS(Joi4, e<int>("abc???????"), e<int>("abc??????"), e<int>("?"));
	ASSERT_PARSE_FAILURE(Joi4, e<int>("??abc???????"));
	ASSERT_PARSE_SUCCESS(Joi4, e<int>("abc??abc???????"), e<int>("abc??"), e<int>("abc???????"));
	ASSERT_PARSE_SUCCESS(Joi4, e<int>("abc ??abc???????"), e<int>("abc"), e<int>(" ??abc???????"));
	ASSERT_PARSE_FAILURE(Joi4, e<int>(""));

	ASSERT_PARSE_SUCCESS(Joi5, e<int>("abcabcabcabc??"), e<int>("abcabcabcabc??"), e<int>(""));
	ASSERT_PARSE_SUCCESS(Joi5, e<int>("abcabcabcabc"), e<int>("abcabcabcabc"), e<int>(""));
	ASSERT_PARSE_SUCCESS(Joi5, e<int>("abcabcabcabc ??"), e<int>("abcabcabcabc"), e<int>(" ??"));
	ASSERT_PARSE_SUCCESS(Joi5, e<int>("abc"), e<int>("abc"), e<int>(""));
	ASSERT_PARSE_FAILURE(Joi5, e<int>(" abc"));
	ASSERT_PARSE_FAILURE(Joi5, e<int>(""));
}

TEST("Join", "Contiguous empty strings")
{
	using J1 = Join<Maybe<choice_parser<ABC, QQ>>>;
	using J2 = Join<ZeroOrMore<sequence_parser<All1, Any2>>>;

	using P = Join<sequence_parser<all_of_parser<TT("**start**")>, J1, J2, all_of_parser<TT("__end__")>>>;
	
	ASSERT_PARSE_SUCCESS(P, "**start**__end__", "**start**__end__", "");

	ASSERT_PARSE_SUCCESS(P, L"**start**__end__", L"**start**__end__", L"");

	ASSERT_PARSE_SUCCESS(P, e<int>("**start**__end__"), e<int>("**start**__end__"), e<int>(""));
}



TEST("Join", "Join<Delimit>")
{
	using D = Delimit<ABC, QQ, integral_constant<false>>;
	using J = Join<D>;

	{
		using vec_type = std::vector<output_span<char>>;
		ASSERT_PARSE_SUCCESS(D, "abc", vec_type({ "abc" }), "");
		ASSERT_PARSE_SUCCESS(D, "abc??abc??a", vec_type({ "abc", "abc" }), "??a");
		ASSERT_PARSE_SUCCESS(D, "abc??abc??abc", vec_type({ "abc", "abc", "abc" }), "");
		ASSERT_PARSE_SUCCESS(J, "abc", "abc", "");
		ASSERT_PARSE_LOOKAHEAD_ONLY(J, "abc??abc??a", "??a");
		ASSERT_PARSE_LOOKAHEAD_ONLY(J, "abc??abc??abc", "");
	}

	{
		using vec_type = std::vector<output_span<wchar_t>>;
		ASSERT_PARSE_SUCCESS(D, L"abc", vec_type({ L"abc" }), L"");
		ASSERT_PARSE_SUCCESS(D, L"abc??abc??a", vec_type({ L"abc", L"abc" }), L"??a");
		ASSERT_PARSE_SUCCESS(D, L"abc??abc??abc", vec_type({ L"abc", L"abc", L"abc" }), L"");
		ASSERT_PARSE_SUCCESS(J, L"abc", L"abc", L"");
		ASSERT_PARSE_LOOKAHEAD_ONLY(J, L"abc??abc??a", L"??a");
		ASSERT_PARSE_LOOKAHEAD_ONLY(J, L"abc??abc??abc", L"");
	}

	{
		using vec_type = std::vector<output_span<int>>;
		ASSERT_PARSE_SUCCESS(D, e<int>("abc"), vec_type({ e<int>("abc") }), e<int>(""));
		ASSERT_PARSE_SUCCESS(D, e<int>("abc??abc??a"), vec_type({ e<int>("abc"), e<int>("abc") }), e<int>("??a"));
		ASSERT_PARSE_SUCCESS(D, e<int>("abc??abc??abc"), vec_type({ e<int>("abc"), e<int>("abc"), e<int>("abc") }), e<int>(""));
		ASSERT_PARSE_SUCCESS(J, e<int>("abc"), e<int>("abc"), e<int>(""));
		ASSERT_PARSE_LOOKAHEAD_ONLY(J, e<int>("abc??abc??a"), e<int>("??a"));
		ASSERT_PARSE_LOOKAHEAD_ONLY(J, e<int>("abc??abc??abc"), e<int>(""));
	}
}

TEST("Join", "Join<ignore_parser>")
{
	using Q = any_of_parser<TT("?")>;

	using S1 = sequence_parser<ABC, ignore_parser<QQ>>;
	using S2 = sequence_parser<ABC, ignore_parser<QQ>, ABC>;
	using S3 = sequence_parser<ABC, QQ, ABC>;
	using S4 = sequence_parser<ABC, Q, Q, ABC>;
	using J1 = Join<S1>;
	using J2 = Join<S2>;
	using J3 = Join<S3>;
	using J4 = Join<S4>;

	ASSERT_PARSE_SUCCESS(S1, "abc??abc", "abc", "abc");
	ASSERT_PARSE_SUCCESS(S1, "abc??abc??a", "abc", "abc??a");
	ASSERT_PARSE_SUCCESS(J1, "abc??abc", "abc", "abc");
	ASSERT_PARSE_SUCCESS(J1, "abc??abc??a", "abc", "abc??a");

	ASSERT_PARSE_SUCCESS(S2, "abc??abc", std::tuple("abc", "abc"), "");
	ASSERT_PARSE_SUCCESS(S2, "abc??abc??a", std::tuple("abc", "abc"), "??a");
	ASSERT_PARSE_LOOKAHEAD_ONLY(J2, "abc??abc", "");
	ASSERT_PARSE_LOOKAHEAD_ONLY(J2, "abc??abc??a", "??a");

	ASSERT_PARSE_SUCCESS(S3, "abc??abc", std::tuple("abc", "??", "abc"), "");
	ASSERT_PARSE_SUCCESS(S3, "abc??abc??a", std::tuple("abc", "??", "abc"), "??a");
	ASSERT_PARSE_SUCCESS(J3, "abc??abc", "abc??abc", "");
	ASSERT_PARSE_SUCCESS(J3, "abc??abc??a", "abc??abc", "??a");

	ASSERT_PARSE_SUCCESS(S4, "abc??abc", std::tuple("abc", "?", "?", "abc"), "");
	ASSERT_PARSE_SUCCESS(S4, "abc??abc??a", std::tuple("abc", "?", "?", "abc"), "??a");
	ASSERT_PARSE_SUCCESS(J4, "abc??abc", "abc??abc", "");
	ASSERT_PARSE_SUCCESS(J4, "abc??abc??a", "abc??abc", "??a");

	ASSERT_PARSE_SUCCESS(S1, L"abc??abc", L"abc", L"abc");
	ASSERT_PARSE_SUCCESS(S1, L"abc??abc??a", L"abc", L"abc??a");
	ASSERT_PARSE_SUCCESS(J1, L"abc??abc", L"abc", L"abc");
	ASSERT_PARSE_SUCCESS(J1, L"abc??abc??a", L"abc", L"abc??a");

	ASSERT_PARSE_SUCCESS(S2, L"abc??abc", std::tuple(L"abc", L"abc"), L"");
	ASSERT_PARSE_SUCCESS(S2, L"abc??abc??a", std::tuple(L"abc", L"abc"), L"??a");
	ASSERT_PARSE_LOOKAHEAD_ONLY(J2, L"abc??abc", L"");
	ASSERT_PARSE_LOOKAHEAD_ONLY(J2, L"abc??abc??a", L"??a");

	ASSERT_PARSE_SUCCESS(S3, L"abc??abc", std::tuple(L"abc", L"??", L"abc"), L"");
	ASSERT_PARSE_SUCCESS(S3, L"abc??abc??a", std::tuple(L"abc", L"??", L"abc"), L"??a");
	ASSERT_PARSE_SUCCESS(J3, L"abc??abc", L"abc??abc", L"");
	ASSERT_PARSE_SUCCESS(J3, L"abc??abc??a", L"abc??abc", L"??a");

	ASSERT_PARSE_SUCCESS(S4, L"abc??abc", std::tuple(L"abc", L"?", L"?", L"abc"), L"");
	ASSERT_PARSE_SUCCESS(S4, L"abc??abc??a", std::tuple(L"abc", L"?", L"?", L"abc"), L"??a");
	ASSERT_PARSE_SUCCESS(J4, L"abc??abc", L"abc??abc", L"");
	ASSERT_PARSE_SUCCESS(J4, L"abc??abc??a", L"abc??abc", L"??a");

	ASSERT_PARSE_SUCCESS(S1, e<int>("abc??abc"), e<int>("abc"), e<int>("abc"));
	ASSERT_PARSE_SUCCESS(S1, e<int>("abc??abc??a"), e<int>("abc"), e<int>("abc??a"));
	ASSERT_PARSE_SUCCESS(J1, e<int>("abc??abc"), e<int>("abc"), e<int>("abc"));
	ASSERT_PARSE_SUCCESS(J1, e<int>("abc??abc??a"), e<int>("abc"), e<int>("abc??a"));

	ASSERT_PARSE_SUCCESS(S2, e<int>("abc??abc"), std::tuple(e<int>("abc"), e<int>("abc")), e<int>(""));
	ASSERT_PARSE_SUCCESS(S2, e<int>("abc??abc??a"), std::tuple(e<int>("abc"), e<int>("abc")), e<int>("??a"));
	ASSERT_PARSE_LOOKAHEAD_ONLY(J2, e<int>("abc??abc"), e<int>(""));
	ASSERT_PARSE_LOOKAHEAD_ONLY(J2, e<int>("abc??abc??a"), e<int>("??a"));

	ASSERT_PARSE_SUCCESS(S3, e<int>("abc??abc"), std::tuple(e<int>("abc"), e<int>("??"), e<int>("abc")), e<int>(""));
	ASSERT_PARSE_SUCCESS(S3, e<int>("abc??abc??a"), std::tuple(e<int>("abc"), e<int>("??"), e<int>("abc")), e<int>("??a"));
	ASSERT_PARSE_SUCCESS(J3, e<int>("abc??abc"), e<int>("abc??abc"), e<int>(""));
	ASSERT_PARSE_SUCCESS(J3, e<int>("abc??abc??a"), e<int>("abc??abc"), e<int>("??a"));

	ASSERT_PARSE_SUCCESS(S4, e<int>("abc??abc"), std::tuple(e<int>("abc"), e<int>("?"), e<int>("?"), e<int>("abc")), e<int>(""));
	ASSERT_PARSE_SUCCESS(S4, e<int>("abc??abc??a"), std::tuple(e<int>("abc"), e<int>("?"), e<int>("?"), e<int>("abc")), e<int>("??a"));
	ASSERT_PARSE_SUCCESS(J4, e<int>("abc??abc"), e<int>("abc??abc"), e<int>(""));
	ASSERT_PARSE_SUCCESS(J4, e<int>("abc??abc??a"), e<int>("abc??abc"), e<int>("??a"));
}

TEST("Join", "Join<map_parser>")
{
	constexpr auto f = [](auto&& v)
	{
		using V = std::ranges::range_value_t<decltype(v)>;
		if constexpr (std::same_as<V, char> or std::same_as<V, output_span<char>>)
			return output_span<char>((v.size() % 2 == 0) ? "a" : "b");
		else if constexpr (std::same_as<V, wchar_t> or std::same_as<V, output_span<wchar_t>>)
			return output_span<wchar_t>((v.size() % 2 == 0) ? L"a" : L"b");
		else if constexpr (std::same_as<V, int> or std::same_as<V, output_span<int>>)
		{
			constexpr auto a = e<int>("a");
			constexpr auto b = e<int>("b");
			return output_span<int>((v.size() % 2 == 0) ? a : b);
		}
		else
			static_assert(std::same_as<V, void>);
	};

	using T1 = map_parser<ABC, integral_constant<f>>;
	using T2 = sequence_parser<map_parser<ABC, integral_constant<f>>, QQ>;
	using T3 = ZeroOrMore<sequence_parser<map_parser<OneOrMore<ABC>, integral_constant<f>>, QQ>>;
	using J1 = Join<T1>;
	using J2 = Join<T2>;
	using J3 = Join<T3>;

	{
		ASSERT_PARSE_SUCCESS(T1, "abcabc", "b", "abc");
		ASSERT_PARSE_SUCCESS(T1, "abc", "b", "");
		ASSERT_PARSE_FAILURE(T1, "");
		ASSERT_PARSE_SUCCESS(J1, "abcabc", "b", "abc");
		ASSERT_PARSE_SUCCESS(J1, "abc", "b", "");
		ASSERT_PARSE_FAILURE(J1, "");

		ASSERT_PARSE_SUCCESS(T2, "abc??abc", std::tuple("b", "??"), "abc");
		ASSERT_PARSE_SUCCESS(T2, "abc??", std::tuple("b", "??"), "");
		ASSERT_PARSE_LOOKAHEAD_ONLY(J2, "abc??abc", "abc");
		ASSERT_PARSE_LOOKAHEAD_ONLY(J2, "abc??", "");

		using vec_type = std::vector<std::tuple<output_span<char>, output_span<char>>>;
		ASSERT_PARSE_SUCCESS(T3, "abcabc??abc??ab", vec_type({ { "a", "??" }, { "b", "??" } }), "ab");
		ASSERT_PARSE_SUCCESS(T3, "abc??abcabcabcabc??", vec_type({ { "b", "??" }, { "a", "??" } }), "");
		ASSERT_PARSE_LOOKAHEAD_ONLY(J3, "abcabc??abc??ab", "ab");
		ASSERT_PARSE_LOOKAHEAD_ONLY(J3, "abc??abcabcabcabc??", "");
	}

	{
		ASSERT_PARSE_SUCCESS(T1, L"abcabc", L"b", L"abc");
		ASSERT_PARSE_SUCCESS(T1, L"abc", L"b", L"");
		ASSERT_PARSE_FAILURE(T1, L"");
		ASSERT_PARSE_SUCCESS(J1, L"abcabc", L"b", L"abc");
		ASSERT_PARSE_SUCCESS(J1, L"abc", L"b", L"");
		ASSERT_PARSE_FAILURE(J1, L"");
		
		ASSERT_PARSE_SUCCESS(T2, L"abc??abc", std::tuple(L"b", L"??"), L"abc");
		ASSERT_PARSE_SUCCESS(T2, L"abc??", std::tuple(L"b", L"??"), L"");
		ASSERT_PARSE_LOOKAHEAD_ONLY(J2, L"abc??abc", L"abc");
		ASSERT_PARSE_LOOKAHEAD_ONLY(J2, L"abc??", L"");

		using vec_type = std::vector<std::tuple<output_span<wchar_t>, output_span<wchar_t>>>;
		ASSERT_PARSE_SUCCESS(T3, L"abcabc??abc??ab", vec_type({ { L"a", L"??" }, { L"b", L"??" } }), L"ab");
		ASSERT_PARSE_SUCCESS(T3, L"abc??abcabcabcabc??", vec_type({ { L"b", L"??" }, { L"a", L"??" } }), L"");
		ASSERT_PARSE_LOOKAHEAD_ONLY(J3, L"abcabc??abc??ab", L"ab");
		ASSERT_PARSE_LOOKAHEAD_ONLY(J3, L"abc??abcabcabcabc??", L"");
	}

	{
		// TODO: The commented out lines have different compile-time and run-time results
		//ASSERT_PARSE_SUCCESS(T1, e<int>("abcabc"), e<int>("b"), e<int>("abc"));
		//ASSERT_PARSE_SUCCESS(T1, e<int>("abc"), e<int>("b"), e<int>(""));
		ASSERT_PARSE_FAILURE(T1, e<int>(""));
		//ASSERT_PARSE_SUCCESS(J1, e<int>("abcabc"), e<int>("b"), e<int>("abc"));
		//ASSERT_PARSE_SUCCESS(J1, e<int>("abc"), e<int>("b"), e<int>(""));
		ASSERT_PARSE_FAILURE(J1, e<int>(""));

		//ASSERT_PARSE_SUCCESS(T2, e<int>("abc??abc"), std::tuple(e<int>("b"), e<int>("??")), e<int>("abc"));
		//ASSERT_PARSE_SUCCESS(T2, e<int>("abc??"), std::tuple(e<int>("b"), e<int>("??")), e<int>(""));
		ASSERT_PARSE_LOOKAHEAD_ONLY(J2, e<int>("abc??abc"), e<int>("abc"));
		ASSERT_PARSE_LOOKAHEAD_ONLY(J2, e<int>("abc??"), e<int>(""));

		using vec_type = std::vector<std::tuple<output_span<int>, output_span<int>>>;
		//ASSERT_PARSE_SUCCESS(T3, e<int>("abcabc??abc??ab"), vec_type({ { e<int>("a"), e<int>("??") }, { e<int>("b"), e<int>("??") } }), e<int>("ab"));
		//ASSERT_PARSE_SUCCESS(T3, e<int>("abc??abcabcabcabc??"), vec_type({ { e<int>("b"), e<int>("??") }, { e<int>("a"), e<int>("??") } }), e<int>(""));
		ASSERT_PARSE_LOOKAHEAD_ONLY(J3, e<int>("abcabc??abc??ab"), e<int>("ab"));
		ASSERT_PARSE_LOOKAHEAD_ONLY(J3, e<int>("abc??abcabcabcabc??"), e<int>(""));
	}
}

TEST("Join", "Join<sequence_parser<choice_parser<non-eps,eps>, anything>>")
{
	auto seq = (TT("+-"_any) | eps) >> TT("abc"_all);
	using Seq = decltype(seq);
	ASSERT_IS_PARSER(Seq, char, sequence_family, std::tuple<output_span<char>,output_span<char>>);
	ASSERT_IS_PARSER(Seq, wchar_t, sequence_family, std::tuple<output_span<wchar_t>,output_span<wchar_t>>);
	ASSERT_IS_PARSER(Seq, int, sequence_family, std::tuple<output_span<int>,output_span<int>>);

	using P = Join<Seq>;

	ASSERT_PARSE_SUCCESS(P, "+abcd", "+abc", "d");
	ASSERT_PARSE_SUCCESS(P, "-abcd", "-abc", "d");
	ASSERT_PARSE_SUCCESS(P, "abcd", "abc", "d");
	ASSERT_PARSE_FAILURE(P, " abcd");
	
	ASSERT_PARSE_SUCCESS(P, L"+abcd", L"+abc", L"d");
	ASSERT_PARSE_SUCCESS(P, L"-abcd", L"-abc", L"d");
	ASSERT_PARSE_SUCCESS(P, L"abcd", L"abc", L"d");
	ASSERT_PARSE_FAILURE(P, L" abcd");
	
	ASSERT_PARSE_SUCCESS(P, e<int>("+abcd"), e<int>("+abc"), e<int>("d"));
	ASSERT_PARSE_SUCCESS(P, e<int>("-abcd"), e<int>("-abc"), e<int>("d"));
	ASSERT_PARSE_SUCCESS(P, e<int>("abcd"), e<int>("abc"), e<int>("d"));
	ASSERT_PARSE_FAILURE(P, e<int>(" abcd"));
}
