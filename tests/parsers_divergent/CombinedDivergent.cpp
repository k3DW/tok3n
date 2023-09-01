#include "pch.h"

FIXTURE("Combined divergent");

TEST("Combined divergent", "Join<Delimit>")
{
	using D = Delimit<ABC, QQ, Const<false>>;
	using J = Join<D>;

	using vec_type = std::vector<std::string_view>;

	ASSERT_PARSE_SUCCESS(D, "abc", vec_type({ "abc" }), "");
	ASSERT_PARSE_SUCCESS(D, "abc??abc??a", vec_type({ "abc", "abc" }), "??a");
	ASSERT_PARSE_SUCCESS(D, "abc??abc??abc", vec_type({ "abc", "abc", "abc" }), "");
	ASSERT_PARSE_SUCCESS(J, "abc", "abc", "");
	ASSERT_PARSE_LOOKAHEAD_ONLY(J, "abc??abc??a", "??a");
	ASSERT_PARSE_LOOKAHEAD_ONLY(J, "abc??abc??abc", "");
}

TEST("Combined divergent", "Sequence<Ignore>")
{
	using P = Sequence<ABC, Ignore<QQ>, ABC>;

	ASSERT_PARSE_SUCCESS(P, "abc??abc??", std::tuple("abc", "abc"), "??");
	ASSERT_PARSE_FAILURE(P, "abcabc??");
}

TEST("Combined divergent", "Join<Ignore>")
{
	using Q = OneChar<"?">;

	using S1 = Sequence<ABC, Ignore<QQ>>;
	using S2 = Sequence<ABC, Ignore<QQ>, ABC>;
	using S3 = Sequence<ABC, QQ, ABC>;
	using S4 = Sequence<ABC, Q, Q, ABC>;
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
}

TEST("Combined divergent", "Join<Transform>")
{
	constexpr auto f = [](auto&& v) -> std::string_view { return (v.size() % 2 == 0) ? "a" : "b"; };

	using T1 = Transform<ABC, Const<f>>;
	using T2 = Sequence<Transform<ABC, Const<f>>, QQ>;
	using T3 = ZeroOrMore<Sequence<Transform<OneOrMore<ABC>, Const<f>>, QQ>>;
	using J1 = Join<T1>;
	using J2 = Join<T2>;
	using J3 = Join<T3>;

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

	using vec_type = std::vector<std::tuple<std::string_view, std::string_view>>;
	ASSERT_PARSE_SUCCESS(T3, "abcabc??abc??ab", vec_type({ { "a", "??" }, { "b", "??" } }), "ab");
	ASSERT_PARSE_SUCCESS(T3, "abc??abcabcabcabc??", vec_type({ { "b", "??" }, { "a", "??" } }), "");
	ASSERT_PARSE_LOOKAHEAD_ONLY(J3, "abcabc??abc??ab", "ab");
	ASSERT_PARSE_LOOKAHEAD_ONLY(J3, "abc??abcabcabcabc??", "");
}