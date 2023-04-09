#include "pch.h"

TOK3N_BEGIN_NAMESPACE_TESTS(basic::OneChar)

using Single = OneChar<'a'>;
using Multi  = OneChar<"abc">;

inline void requirements()
{
	assert
		, IsParser<Single, OneCharType, std::string_view>
		, IsParser<Multi, OneCharType, std::string_view>
		;
}

inline void parse_single()
{
	assert
		, parse<Single>("ab").success("a", "b")
		, parse<Single>("ba").failure()
		, parse<Single>("abc").success("a", "bc")
		, parse<Single>("Ab").failure()
		, parse<Single>("Abc").failure()
		, parse<Single>(" abc").failure()
		;
}

inline void parse_multi()
{
	assert
		, parse<Multi>("abc").success("a", "bc")
		, parse<Multi>("acb").success("a", "cb")
		, parse<Multi>("bac").success("b", "ac")
		, parse<Multi>("bca").success("b", "ca")
		, parse<Multi>("cab").success("c", "ab")
		, parse<Multi>("cba").success("c", "ba")
		, parse<Multi>("ABC").failure()
		, parse<Multi>("ACB").failure()
		, parse<Multi>("BAC").failure()
		, parse<Multi>("BCA").failure()
		, parse<Multi>("CAB").failure()
		, parse<Multi>("CBA").failure()
		, parse<Multi>("dcba").failure()
		, parse<Multi>(" cba").failure()
		;
}



using constructible = traits::basic::constructible<OneChar>;

inline void constructible_from_ascii_only()
{
	using all_ascii_chars = std::make_integer_sequence<int, 128>;
	using all_non_ascii_chars = decltype([]<int... Is>(std::integer_sequence<int, Is...>) { return std::integer_sequence<int, (Is - 128)...>{}; }(all_ascii_chars{}));

	assert
		, constructible::from_all_chars<all_ascii_chars>
		, not constructible::from_any_char<all_non_ascii_chars>
		;
}

inline void constructible_alphabetically_only()
{
	assert
		, constructible::from<"abc">
		, not constructible::from<"acb">
		, not constructible::from<"bac">
		, not constructible::from<"bca">
		, not constructible::from<"cab">
		, not constructible::from<"cba">
		;
}

inline void parse_empty()
{
	assert
		, constructible::from<"">
		, parse<OneChar<"">>("anything").failure()
		, parse<OneChar<"">>("").failure()
		;
}

TOK3N_END_NAMESPACE_TESTS(basic::OneChar)
