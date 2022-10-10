#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::combine)

using L1 = Literal<"abc">;
constexpr L1 l1;
using L2 = Literal<"??">;
constexpr L2 l2;

void Join_Delimit()
{
	constexpr auto d = delimit(l1, l2);
	constexpr auto j = d % join;

	assert
		, parse(d, "abc").success({ "abc" }, "")
		, parse(d, "abc??abc??a").success({ "abc", "abc" }, "??a")
		, parse(d, "abc??abc??abc").success({ "abc", "abc", "abc" }, "")
		, parse(j, "abc").success("abc", "")
		, parse(j, "abc??abc??a").failure("abc??abc??a")
		, parse(j, "abc??abc??abc").failure("abc??abc??abc")
		;
}

void Ignore_Sequence()
{
	constexpr auto p = l1 >> ignore(l2) >> l1;

	assert
		, parse(p, "abc??abc??").success({ "abc", "abc" }, "??")
		, parse(p, "abcabc??").failure("abcabc??")
		;
}

void Join_Ignore()
{
	constexpr auto q = OneChar<"?">{};

	constexpr auto s1 = l1 >> ignore(l2);
	constexpr auto s2 = l1 >> ignore(l2) >> l1;
	constexpr auto s3 = l1 >> l2 >> l1;
	constexpr auto s4 = l1 >> q >> q >> l1;
	constexpr auto j1 = s1 % join;
	constexpr auto j2 = s2 % join;
	constexpr auto j3 = s3 % join;
	constexpr auto j4 = s4 % join;

	assert
		, parse(s1, "abc??abc").success("abc", "abc")
		, parse(s1, "abc??abc??a").success("abc", "abc??a")
		, parse(j1, "abc??abc").success("abc", "abc")
		, parse(j1, "abc??abc??a").success("abc", "abc??a")

		, parse(s2, "abc??abc").success({ "abc", "abc" }, "")
		, parse(s2, "abc??abc??a").success({ "abc", "abc" }, "??a")
		, parse(j2, "abc??abc").failure("abc??abc")
		, parse(j2, "abc??abc??a").failure("abc??abc??a")

		, parse(s3, "abc??abc").success("abc??abc", "")
		, parse(s3, "abc??abc??a").success("abc??abc", "??a")
		, parse(j3, "abc??abc").success("abc??abc", "")
		, parse(j3, "abc??abc??a").success("abc??abc", "??a")

		, parse(s4, "abc??abc").success({ "abc", "?", "?", "abc" }, "")
		, parse(s4, "abc??abc??a").success({ "abc", "?", "?", "abc" }, "??a")
		, parse(j4, "abc??abc").success("abc??abc", "")
		, parse(j4, "abc??abc??a").success("abc??abc", "??a")
		;
}

void Join_Transform()
{
	constexpr auto f = fn<[](auto&& v) -> std::string_view { return (v.size() % 2 == 0) ? "a" : "b"; }>;

	constexpr auto t1 = l1 % f;
	constexpr auto t2 = (l1 % f) >> l2;
	constexpr auto t3 = *((+l1 % f) >> l2);
	constexpr auto j1 = t1 % join;
	constexpr auto j2 = t2 % join;
	constexpr auto j3 = t3 % join;

	assert
		, parse(t1, "abcabc").success("b", "abc")
		, parse(t1, "abc").success("b", "")
		, parse(t1, "").failure("")
		, parse(j1, "abcabc").success("b", "abc")
		, parse(j1, "abc").success("b", "")
		, parse(j1, "").failure("")

		, parse(t2, "abc??abc").success({ "b", "??" }, "abc")
		, parse(t2, "abc??").success({ "b", "??" }, "")
		, parse(j2, "abc??abc").failure("abc??abc")
		, parse(j2, "abc??").failure("abc??")

		, parse(t3, "abcabc??abc??ab").success({ { "a", "??" }, { "b", "??" } }, "ab")
		, parse(t3, "abc??abcabcabcabc??").success({ { "b", "??" }, { "a", "??" } }, "")
		, parse(j3, "abcabc??abc??ab").failure("abcabc??abc??ab")
		, parse(j3, "abc??abcabcabcabc??").failure("abc??abcabcabcabc??")
		;
}

TOK3N_END_NAMESPACE_TESTS(adaptor::combine)
