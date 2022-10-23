#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(compound::Sequence)

using constructible = traits::compound::constructible<Sequence>;

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
		;
}
void requirements_threeway()
{
	assert
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

TOK3N_END_NAMESPACE_TESTS(compound::Sequence)
