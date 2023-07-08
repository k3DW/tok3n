#include "pch.h"

using TwoWay = Seq1;
using ThreeWay = Seq3;

TEST("Sequence", "Requirements")
{
	assert
		, IsParser<TwoWay, SequenceType, std::tuple<std::string_view, std::string_view>>
		, IsParser<ThreeWay, SequenceType, std::tuple<std::string_view, std::string_view, std::string_view>>
		;
}

TEST("Sequence", "Parse two-way Sequence")
{
	ASSERT_PARSE_FAILURE(TwoWay, "abc");
	ASSERT_PARSE_FAILURE(TwoWay, "abcd");
	ASSERT_PARSE_SUCCESS(TwoWay, "abef", std::tuple("ab", "e"), "f");
	ASSERT_PARSE_SUCCESS(TwoWay, "ab ef", std::tuple("ab", " "), "ef");
}

TEST("Sequence", "Parse three-way Sequence")
{
	ASSERT_PARSE_SUCCESS(ThreeWay, "abcde", std::tuple("ab", "c", "d"), "e");
	ASSERT_PARSE_SUCCESS(ThreeWay, "abdc", std::tuple("ab", "d", "c"), "");
	ASSERT_PARSE_FAILURE(ThreeWay, "abcz");
}



using constructible = traits::compound::constructible<Sequence>;

TEST("Sequence", "Not constructible empty")
{
	assert, not constructible::from<>;
}
