#include "pch.h"

#ifdef TOK3N_TESTING
TOK3N_BEGIN_NAMESPACE_TESTS(compound::Choice)

using namespace samples::all;

using TwoWay1 = Cho1;
using TwoWay2 = Cho2;

using ThreeWay1 = Cho3;
using ThreeWay2 = Cho4;

void requirements()
{
	assert
		, is_parser<TwoWay1>
		, TwoWay1::type == ParserType::Choice
		, ParserResultOf<TwoWay1>::is<std::string_view>

		, is_parser<TwoWay2>
		, TwoWay2::type == ParserType::Choice
		, ParserResultOf<TwoWay2>::is<std::string_view>

		, is_parser<ThreeWay1>
		, ThreeWay1::type == ParserType::Choice
		, ParserResultOf<ThreeWay1>::is<std::string_view>

		, is_parser<ThreeWay2>
		, ThreeWay2::type == ParserType::Choice
		, ParserResultOf<ThreeWay2>::is<std::string_view>
		;
}

void parse_twoway()
{
	assert
		, parse<TwoWay1>("abc").success("ab", "c")
		, parse<TwoWay1>("ba").success("b", "a")
		, parse<TwoWay1>("cba").failure()
		, parse<TwoWay1>("dcba").failure()
		, parse<TwoWay1>("edcba").success("e", "dcba")

		, parse<TwoWay2>("abc").success("a", "bc")
		, parse<TwoWay2>("ba").success("b", "a")
		, parse<TwoWay2>("cba").failure()
		, parse<TwoWay2>("dcba").failure()
		, parse<TwoWay2>("edcba").success("e", "dcba")
		;
}

void parse_threeway()
{
	assert
		, parse<ThreeWay1>("abc").success("ab", "c")
		, parse<ThreeWay1>("ba").success("b", "a")
		, parse<ThreeWay1>("cba").success("c", "ba")
		, parse<ThreeWay1>("dcba").success("d", "cba")
		, parse<ThreeWay1>("edcba").success("e", "dcba")

		, parse<ThreeWay2>("abc").success("a", "bc")
		, parse<ThreeWay2>("ba").success("b", "a")
		, parse<ThreeWay2>("cba").success("c", "ba")
		, parse<ThreeWay2>("dcba").success("d", "cba")
		, parse<ThreeWay2>("edcba").success("e", "dcba")

		, parse<ThreeWay1>("zyx").failure()
		, parse<ThreeWay1>("xyz").success("x", "yz")
		, parse<ThreeWay2>("zyx").failure()
		, parse<ThreeWay2>("xyz").success("x", "yz")
		;
}



using constructible = traits::compound::constructible<Choice>;

void constructible_same_result_type()
{
	assert
		, constructible::from<OC1, OC3, NC2, NC1, L2>
		, not constructible::from<OC1, Sequence<OC2, OC3>>
		;
}

void not_constructible_empty()
{
	assert, not constructible::from<>;
}

TOK3N_END_NAMESPACE_TESTS(compound::Choice)
#endif
