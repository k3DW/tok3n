#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(compound::Choice)

struct constructible
{
	template <class... Ps>
	static constexpr bool from = requires { typename Choice<Ps...>; };
};

void constructible_same_result_type()
{
	assert
		, constructible::from<OneChar<'a'>, OneChar<"bc">, NotChar<'d'>, NotChar<"ef">, Literal<"literal">>
		, not constructible::from<OneChar<"a">, Sequence<OneChar<"b">, OneChar<"c">>>
		;
}

void not_constructible_empty()
{
	assert, not constructible::from<>;
}



using TwoWay1 = Choice<Literal<"ab">, NotChar<"cd">>;
constexpr TwoWay1 twoway1;

using TwoWay2 = Choice<NotChar<"cd">, Literal<"ab">>;
constexpr TwoWay2 twoway2;

using ThreeWay1 = Choice<Literal<"ab">, OneChar<"cd">, NotChar<'z'>>;
constexpr ThreeWay1 threeway1;

using ThreeWay2 = Choice<NotChar<'z'>, Literal<"ab">, OneChar<"cd">>;
constexpr ThreeWay2 threeway2;

void requirements_twoway()
{
	assert
		, is_parser<TwoWay1>
		, parser_type_of<TwoWay1>.is_Choice
		, result_of<TwoWay1>.is<std::string_view>

		, is_parser<TwoWay2>
		, parser_type_of<TwoWay2>.is_Choice
		, result_of<TwoWay2>.is<std::string_view>
		;
}
void requirements_threeway()
{
	assert
		, is_parser<ThreeWay1>
		, parser_type_of<ThreeWay1>.is_Choice
		, result_of<ThreeWay1>.is<std::string_view>

		, is_parser<ThreeWay2>
		, parser_type_of<ThreeWay2>.is_Choice
		, result_of<ThreeWay2>.is<std::string_view>
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

TOK3N_END_NAMESPACE_TESTS(compound::Choice)
