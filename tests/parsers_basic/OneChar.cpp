#include "pch.h"

using Single = OneChar<'a'>;
using Multi  = OneChar<"abc">;

TEST("OneChar", "Requirements")
{
	assert
		, IsParser<Single, OneCharType, std::string_view>
		, IsParser<Multi, OneCharType, std::string_view>
		;
}

TEST("OneChar", "Parse single char")
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

TEST("OneChar", "Parse multi char")
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

TEST("OneChar", "Constructible from ascii only")
{
	using all_ascii_chars = std::make_integer_sequence<int, 128>;
	using all_non_ascii_chars = decltype([]<int... Is>(std::integer_sequence<int, Is...>) { return std::integer_sequence<int, (Is - 128)...>{}; }(all_ascii_chars{}));

	assert
		, constructible::from_all_chars<all_ascii_chars>
		, constructible::from_any_char<all_non_ascii_chars>
		;
}

TEST("OneChar", "Constructible from lexicographically sorted only")
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

TEST("OneChar", "Parse empty")
{
	assert
		, constructible::from<"">
		, parse<OneChar<"">>("anything").failure()
		, parse<OneChar<"">>("").failure()
		;
}
