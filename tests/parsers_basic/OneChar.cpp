#include "pch.h"

using Single = OneChar<'a'>;
using Multi  = OneChar<"abc">;

TEST("OneChar", "Requirements")
{
	ASSERT_IS_PARSER(Single, OneCharType, std::string_view);
	ASSERT_IS_PARSER(Multi, OneCharType, std::string_view);
}

TEST("OneChar", "Parse single char")
{
	ASSERT_PARSE_SUCCESS(Single, "ab", "a", "b");
	ASSERT_PARSE_FAILURE(Single, "ba");
	ASSERT_PARSE_SUCCESS(Single, "abc", "a", "bc");
	ASSERT_PARSE_FAILURE(Single, "Ab");
	ASSERT_PARSE_FAILURE(Single, "Abc");
	ASSERT_PARSE_FAILURE(Single, " abc");
}

TEST("OneChar", "Parse multi char")
{
	ASSERT_PARSE_SUCCESS(Multi, "abc", "a", "bc");
	ASSERT_PARSE_SUCCESS(Multi, "acb", "a", "cb");
	ASSERT_PARSE_SUCCESS(Multi, "bac", "b", "ac");
	ASSERT_PARSE_SUCCESS(Multi, "bca", "b", "ca");
	ASSERT_PARSE_SUCCESS(Multi, "cab", "c", "ab");
	ASSERT_PARSE_SUCCESS(Multi, "cba", "c", "ba");
	ASSERT_PARSE_FAILURE(Multi, "ABC");
	ASSERT_PARSE_FAILURE(Multi, "ACB");
	ASSERT_PARSE_FAILURE(Multi, "BAC");
	ASSERT_PARSE_FAILURE(Multi, "BCA");
	ASSERT_PARSE_FAILURE(Multi, "CAB");
	ASSERT_PARSE_FAILURE(Multi, "CBA");
	ASSERT_PARSE_FAILURE(Multi, "dcba");
	ASSERT_PARSE_FAILURE(Multi, " cba");
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
	ASSERT_PARSER_BASIC_CONSTRUCTIBLE(OneChar, "abc");
	ASSERT_PARSER_BASIC_NOT_CONSTRUCTIBLE(OneChar, "acb");
	ASSERT_PARSER_BASIC_NOT_CONSTRUCTIBLE(OneChar, "bac");
	ASSERT_PARSER_BASIC_NOT_CONSTRUCTIBLE(OneChar, "bca");
	ASSERT_PARSER_BASIC_NOT_CONSTRUCTIBLE(OneChar, "cab");
	ASSERT_PARSER_BASIC_NOT_CONSTRUCTIBLE(OneChar, "cba");
}

TEST("OneChar", "Parse empty")
{
	ASSERT_PARSER_BASIC_CONSTRUCTIBLE(OneChar, "");
	
	ASSERT_PARSE_FAILURE(OneChar<"">, "anything");
	ASSERT_PARSE_FAILURE(OneChar<"">, "");
}
