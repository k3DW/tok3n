#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(basic::OneChar)

using Single = OneChar<'a'>;
constexpr Single single;

using Multi = OneChar<"abc">;
constexpr Multi multi;

void requirements_single()
{
	assert
		, is_parser<Single>
		, parser_type_of<Single>.is_OneChar
		, result_of<Single>.is<std::string_view>
		, Single::parse == single.parse
		, Single::lookahead == single.lookahead
		;
}
void requirements_multi()
{
	assert
		, is_parser<Multi>
		, parser_type_of<Multi>.is_OneChar
		, result_of<Multi>.is<std::string_view>
		, Multi::parse == multi.parse
		, Multi::lookahead == multi.lookahead
		;
}

void parse_single()
{
	assert
		, parse<Single>("ab").success("a", "b")
		, parse<Single>("ba").failure("ba")
		, parse<Single>("abc").success("a", "bc")
		, parse<Single>("Ab").failure("Ab")
		, parse<Single>("Abc").failure("Abc")
		, parse<Single>(" abc").failure(" abc")
		;
}
void parse_multi()
{
	assert
		, parse<Multi>("abc").success("a", "bc")
		, parse<Multi>("acb").success("a", "cb")
		, parse<Multi>("bac").success("b", "ac")
		, parse<Multi>("bca").success("b", "ca")
		, parse<Multi>("cab").success("c", "ab")
		, parse<Multi>("cba").success("c", "ba")
		, parse<Multi>("ABC").failure("ABC")
		, parse<Multi>("ACB").failure("ACB")
		, parse<Multi>("BAC").failure("BAC")
		, parse<Multi>("BCA").failure("BCA")
		, parse<Multi>("CAB").failure("CAB")
		, parse<Multi>("CBA").failure("CBA")
		, parse<Multi>("dcba").failure("dcba")
		, parse<Multi>(" cba").failure(" cba")
		;
}



struct constructible
{
	template <class T>           static constexpr bool from_all = false;
	template <std::size_t... Is> static constexpr bool from_all<std::index_sequence<Is...>> = (... && requires { typename OneChar<(char)Is>; });

	template <class T>           static constexpr bool from_any = false;
	template <std::size_t... Is> static constexpr bool from_any<std::index_sequence<Is...>> = (... || requires { typename OneChar<(char)Is>; });

	template <static_string str> static constexpr bool from_string = requires { typename OneChar<str>; };
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

TOK3N_END_NAMESPACE_TESTS(basic::OneChar)
