#include "pch.h"

using TwoWay = Seq1;
using ThreeWay = Seq3;

inline void requirements()
{
	assert
		, IsParser<TwoWay, SequenceType, std::tuple<std::string_view, std::string_view>>
		, IsParser<ThreeWay, SequenceType, std::tuple<std::string_view, std::string_view, std::string_view>>
		;
}

inline void parse_twoway()
{
	assert
		, parse<TwoWay>("abc").failure()
		, parse<TwoWay>("abcd").failure()
		, parse<TwoWay>("abef").success({ "ab", "e" }, "f")
		, parse<TwoWay>("ab ef").success({ "ab", " " }, "ef")
		;
}

inline void parse_threeway()
{
	assert
		, parse<ThreeWay>("abcde").success({ "ab", "c", "d" }, "e")
		, parse<ThreeWay>("abdc").success({ "ab", "d", "c" }, "")
		, parse<ThreeWay>("abcz").failure()
		;
}



using constructible = traits::compound::constructible<Sequence>;

inline void not_constructible_empty()
{
	assert, not constructible::from<>;
}
