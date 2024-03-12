#include "pch.h"
#include "wchar_t-samples/wchar_t-samples.h"

FIXTURE("Join");

TEST("Join", "Requirements")
{
	ASSERT_IS_PARSER(Joi1, wchar_t, JoinFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Joi2, wchar_t, JoinFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Joi3, wchar_t, JoinFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Joi4, wchar_t, JoinFamily, Output<wchar_t>);
	ASSERT_IS_PARSER(Joi5, wchar_t, JoinFamily, Output<wchar_t>);
}

TEST("Join", "Parse all")
{
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
}

TEST("Join", "Contiguous empty strings")
{
	using J1 = Join<Maybe<Choice<ABC, QQ>>>;
	using J2 = Join<ZeroOrMore<Sequence<All1, Any2>>>;

	using P = Join<Sequence<AllOf<L"**start**">, J1, J2, AllOf<L"__end__">>>;

	ASSERT_PARSE_SUCCESS(P, L"**start**__end__", L"**start**__end__", L"");
}



TEST("Join", "Join<Delimit>")
{
	using D = Delimit<ABC, QQ, Const<false>>;
	using J = Join<D>;

	using vec_type = std::vector<Output<wchar_t>>;

	ASSERT_PARSE_SUCCESS(D, L"abc", vec_type({ L"abc" }), L"");
	ASSERT_PARSE_SUCCESS(D, L"abc??abc??a", vec_type({ L"abc", L"abc" }), L"??a");
	ASSERT_PARSE_SUCCESS(D, L"abc??abc??abc", vec_type({ L"abc", L"abc", L"abc" }), L"");
	ASSERT_PARSE_SUCCESS(J, L"abc", L"abc", L"");
	ASSERT_PARSE_LOOKAHEAD_ONLY(J, L"abc??abc??a", L"??a");
	ASSERT_PARSE_LOOKAHEAD_ONLY(J, L"abc??abc??abc", L"");
}

TEST("Join", "Join<Ignore>")
{
	using Q = AnyOf<L"?">;

	using S1 = Sequence<ABC, Ignore<QQ>>;
	using S2 = Sequence<ABC, Ignore<QQ>, ABC>;
	using S3 = Sequence<ABC, QQ, ABC>;
	using S4 = Sequence<ABC, Q, Q, ABC>;
	using J1 = Join<S1>;
	using J2 = Join<S2>;
	using J3 = Join<S3>;
	using J4 = Join<S4>;

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
}

TEST("Join", "Join<Transform>")
{
	constexpr auto f = [](auto&& v) -> Output<wchar_t> { return (v.size() % 2 == 0) ? L"a" : L"b"; };

	using T1 = Transform<ABC, Const<f>>;
	using T2 = Sequence<Transform<ABC, Const<f>>, QQ>;
	using T3 = ZeroOrMore<Sequence<Transform<OneOrMore<ABC>, Const<f>>, QQ>>;
	using J1 = Join<T1>;
	using J2 = Join<T2>;
	using J3 = Join<T3>;

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

	using vec_type = std::vector<std::tuple<Output<wchar_t>, Output<wchar_t>>>;
	ASSERT_PARSE_SUCCESS(T3, L"abcabc??abc??ab", vec_type({ { L"a", L"??" }, { L"b", L"??" } }), L"ab");
	ASSERT_PARSE_SUCCESS(T3, L"abc??abcabcabcabc??", vec_type({ { L"b", L"??" }, { L"a", L"??" } }), L"");
	ASSERT_PARSE_LOOKAHEAD_ONLY(J3, L"abcabc??abc??ab", L"ab");
	ASSERT_PARSE_LOOKAHEAD_ONLY(J3, L"abc??abcabcabcabc??", L"");
}

