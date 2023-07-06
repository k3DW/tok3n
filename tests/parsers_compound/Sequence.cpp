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
	assert
		, parse<TwoWay>("abc").failure()
		, parse<TwoWay>("abcd").failure()
		, parse<TwoWay>("abef").success({ "ab", "e" }, "f")
		, parse<TwoWay>("ab ef").success({ "ab", " " }, "ef")
		;
}

TEST("Sequence", "Parse three-way Sequence")
{
	assert
		, parse<ThreeWay>("abcde").success({ "ab", "c", "d" }, "e")
		, parse<ThreeWay>("abdc").success({ "ab", "d", "c" }, "")
		, parse<ThreeWay>("abcz").failure()
		;
}



using constructible = traits::compound::constructible<Sequence>;

TEST("Sequence", "Not constructible empty")
{
	assert, not constructible::from<>;
}
