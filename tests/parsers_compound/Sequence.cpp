#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(compound::Sequence)

using namespace samples::all;

using TwoWay = Seq1;
using ThreeWay = Seq3;

void requirements()
{
	assert
		, is_parser<TwoWay>
		, parser_type_of<TwoWay>.is_Sequence
		, result_of<TwoWay>.is<std::tuple<std::string_view, std::string_view>>

		, is_parser<ThreeWay>
		, parser_type_of<ThreeWay>.is_Sequence
		, result_of<ThreeWay>.is<std::tuple<std::string_view, std::string_view, std::string_view>>
		;
}

void parse_twoway()
{
	assert
		, parse<TwoWay>("abc").failure()
		, parse<TwoWay>("abcd").failure()
		, parse<TwoWay>("abef").success({ "ab", "e" }, "f")
		, parse<TwoWay>("ab ef").success({ "ab", " " }, "ef")
		;
}

void parse_threeway()
{
	assert
		, parse<ThreeWay>("abcde").success({ "ab", "c", "d" }, "e")
		, parse<ThreeWay>("abdc").success({ "ab", "d", "c" }, "")
		, parse<ThreeWay>("abcz").failure()
		;
}



using constructible = traits::compound::constructible<Sequence>;

void not_constructible_empty()
{
	assert, not constructible::from<>;
}

TOK3N_END_NAMESPACE_TESTS(compound::Sequence)
#endif