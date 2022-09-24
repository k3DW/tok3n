#include "pch.h"

BEGIN_NAMESPACE_TOK3N(tests::compound::Sequence)

using k3::tok3n::Sequence;



struct constructible
{
	template <class... Ps>
	static constexpr bool from = requires { typename Sequence<Ps...>; };
};

void not_constructible_empty()
{
	assert, not constructible::from<>;
}



using TwoWay = Sequence<Literal<"ab">, NotChar<"cd">>;
constexpr TwoWay twoway;

using ThreeWay = Sequence<Literal<"ab">, OneChar<"cd">, NotChar<'z'>>;
constexpr ThreeWay threeway;

void requirements_twoway()
{
	assert
		, is_parser<TwoWay>
		, parser_type_of<TwoWay>.is_Sequence
		, result_of<TwoWay>.is<std::tuple<std::string_view, std::string_view>>
		, TwoWay::parse == twoway.parse
		, TwoWay::lookahead == twoway.lookahead
		;
}
void requirements_threeway()
{
	assert
		, is_parser<ThreeWay>
		, parser_type_of<ThreeWay>.is_Sequence
		, result_of<ThreeWay>.is<std::tuple<std::string_view, std::string_view, std::string_view>>
		, ThreeWay::parse == threeway.parse
		, ThreeWay::lookahead == threeway.lookahead
		;
}

void parse_twoway()
{
	assert
		, parse<TwoWay>("abc").failure("abc")
		, parse<TwoWay>("abcd").failure("abcd")
		, parse<TwoWay>("abef").success({ "ab", "e" }, "f")
		, parse<TwoWay>("ab ef").success({ "ab", " " }, "ef")
		;
}
void parse_threeway()
{
	assert
		, parse<ThreeWay>("abcde").success({ "ab", "c", "d" }, "e")
		, parse<ThreeWay>("abdc").success({ "ab", "d", "c" }, "")
		, parse<ThreeWay>("abcz").failure("abcz")
		;
}

END_NAMESPACE_TOK3N(tests::compound::Sequence)
