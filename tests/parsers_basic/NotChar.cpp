#include "pch.h"

using Single = NotChar<'a'>;
using Multi  = NotChar<"abc">;

inline void requirements()
{
	assert
		, IsParser<Single, NotCharType, std::string_view>
		, IsParser<Multi, NotCharType, std::string_view>
		;
}

inline void parse_single()
{
	assert
		, parse<Single>("ab").failure()
		, parse<Single>("ba").success("b", "a")
		, parse<Single>("abc").failure()
		, parse<Single>("Ab").success("A", "b")
		, parse<Single>("Abc").success("A", "bc")
		, parse<Single>(" abc").success(" ", "abc")
		;
}

inline void parse_multi()
{
	assert
		, parse<Multi>("abc").failure()
		, parse<Multi>("acb").failure()
		, parse<Multi>("bac").failure()
		, parse<Multi>("bca").failure()
		, parse<Multi>("cab").failure()
		, parse<Multi>("cba").failure()
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



using constructible = traits::basic::constructible<NotChar>;

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
		, parse<NotChar<"">>("anything").success("a", "nything")
		, parse<NotChar<"">>("").failure()
		;
}
