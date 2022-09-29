#include "tests/utility.h"

BEGIN_NAMESPACE_TOK3N_TESTS(basic::NotChar)

using Single = NotChar<'a'>;
constexpr Single single;

using Multi = NotChar<"abc">;
constexpr Multi multi;

void requirements_single()
{
	assert
		, is_parser<Single>
		, parser_type_of<Single>.is_NotChar
		, result_of<Single>.is<std::string_view>
		, Single::parse == single.parse
		, Single::lookahead == single.lookahead
		;
}
void requirements_multi()
{
	assert
		, is_parser<Multi>
		, parser_type_of<Multi>.is_NotChar
		, result_of<Multi>.is<std::string_view>
		, Multi::parse == multi.parse
		, Multi::lookahead == multi.lookahead
		;
}

void parse_single()
{
	assert
		, parse<Single>("ab").failure("ab")
		, parse<Single>("ba").success("b", "a")
		, parse<Single>("abc").failure("abc")
		, parse<Single>("Ab").success("A", "b")
		, parse<Single>("Abc").success("A", "bc")
		, parse<Single>(" abc").success(" ", "abc")
		;
}
void parse_multi()
{
	assert
		, parse<Multi>("abc").failure("abc")
		, parse<Multi>("acb").failure("acb")
		, parse<Multi>("bac").failure("bac")
		, parse<Multi>("bca").failure("bca")
		, parse<Multi>("cab").failure("cab")
		, parse<Multi>("cba").failure("cba")
		, parse<Multi>("ABC").success("A", "BC")
		, parse<Multi>("ACB").success("A", "CB")
		, parse<Multi>("BAC").success("B", "AC")
		, parse<Multi>("BCA").success("B", "CA")
		, parse<Multi>("CAB").success("C", "AB")
		, parse<Multi>("CBA").success("C", "BA")
		, parse<Multi>("dcba").success("d", "cba")
		, parse<Multi>("edcba").success("e", "dcba")
		, parse<Multi>(" cba").success(" ", "cba")
		;
}



struct constructible
{
	template <class T>           static constexpr bool from_all = false;
	template <std::size_t... Is> static constexpr bool from_all<std::index_sequence<Is...>> = (... && requires { typename NotChar<(char)Is>; });

	template <class T>           static constexpr bool from_any = false;
	template <std::size_t... Is> static constexpr bool from_any<std::index_sequence<Is...>> = (... || requires { typename NotChar<(char)Is>; });

	template <static_string str> static constexpr bool from_string = requires { typename NotChar<str>; };
};

void constructible_from_ascii_only()
{
	using all_ascii_chars = std::make_index_sequence<128>;
	using all_non_ascii_chars = decltype([]<std::size_t... Is>(std::index_sequence<Is...>) { return std::index_sequence<(Is - 128)...>{}; }(all_ascii_chars{}));

	assert
		, constructible::from_all<all_ascii_chars>
		, not constructible::from_any<all_non_ascii_chars>
		;
}

void constructible_alphabetically_only()
{
	assert
		, constructible::from_string<"abc">
		, not constructible::from_string<"acb">
		, not constructible::from_string<"bac">
		, not constructible::from_string<"bca">
		, not constructible::from_string<"cab">
		, not constructible::from_string<"cba">
		;
}

void not_constructible_empty()
{
	assert, not constructible::from_string<"">;
}

END_NAMESPACE_TOK3N_TESTS(basic::NotChar)
