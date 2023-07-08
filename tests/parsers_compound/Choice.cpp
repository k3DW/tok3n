#include "pch.h"

using TwoWay1 = Cho1;
using TwoWay2 = Cho2;

using ThreeWay1 = Cho3;
using ThreeWay2 = Cho4;

TEST("Choice", "Requirements")
{
	assert
		, IsParser<TwoWay1, ChoiceType, std::string_view>
		, IsParser<TwoWay2, ChoiceType, std::string_view>
		, IsParser<ThreeWay1, ChoiceType, std::string_view>
		, IsParser<ThreeWay2, ChoiceType, std::string_view>
		;
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



using constructible = traits::compound::constructible<Choice>;

TEST("Choice", "Constructible only from parsers with the same result_type")
{
	assert
		, constructible::from<OC1, OC3, NC2, NC1, L2>
		, not constructible::from<OC1, Sequence<OC2, OC3>>
		;
}

TEST("Choice", "Not constructible empty")
{
	assert, not constructible::from<>;
}
