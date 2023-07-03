#include "pch.h"

using TwoWay = Seq1;
using ThreeWay = Seq3;

static void requirements()
{
	assert
		, IsParser<TwoWay, SequenceType, std::tuple<std::string_view, std::string_view>>
		, IsParser<ThreeWay, SequenceType, std::tuple<std::string_view, std::string_view, std::string_view>>
		;
}

static void parse_twoway()
{
	assert
		, parse<TwoWay>("abc").failure()
		, parse<TwoWay>("abcd").failure()
		, parse<TwoWay>("abef").success({ "ab", "e" }, "f")
		, parse<TwoWay>("ab ef").success({ "ab", " " }, "ef")
		;
}

static void parse_threeway()
{
	assert
		, parse<ThreeWay>("abcde").success({ "ab", "c", "d" }, "e")
		, parse<ThreeWay>("abdc").success({ "ab", "d", "c" }, "")
		, parse<ThreeWay>("abcz").failure()
		;
}



using constructible = traits::compound::constructible<Sequence>;

static void not_constructible_empty()
{
	assert, not constructible::from<>;
}

void Sequence_tests()
{
	requirements();
	parse_twoway();
	parse_threeway();
	not_constructible_empty();
}
