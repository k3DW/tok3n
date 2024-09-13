#include "samples.h"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("Named");

TEST("Named", "Requirements")
{
	ASSERT_PARSER_VALUE_TYPE(Nam1, value_type);
	ASSERT_PARSER_VALUE_TYPE(Nam2, value_type);
	ASSERT_PARSER_VALUE_TYPE(Nam3, value_type);
	ASSERT_PARSER_VALUE_TYPE(Nam4, value_type);

	ASSERT_IS_PARSER(Nam1, char, named_family, output_span<char>);
	ASSERT_IS_PARSER(Nam2, char, named_family, std::vector<output_span<char>>);
	ASSERT_IS_PARSER(Nam3, char, named_family, std::optional<output_span<char>>);
	ASSERT_IS_PARSER(Nam4, char, named_family, std::tuple<output_span<char>, std::vector<output_span<char>>>);

	ASSERT_IS_PARSER(Nam1, wchar_t, named_family, output_span<wchar_t>);
	ASSERT_IS_PARSER(Nam2, wchar_t, named_family, std::vector<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Nam3, wchar_t, named_family, std::optional<output_span<wchar_t>>);
	ASSERT_IS_PARSER(Nam4, wchar_t, named_family, std::tuple<output_span<wchar_t>, std::vector<output_span<wchar_t>>>);

	ASSERT_IS_PARSER(Nam1, int, named_family, output_span<int>);
	ASSERT_IS_PARSER(Nam2, int, named_family, std::vector<output_span<int>>);
	ASSERT_IS_PARSER(Nam3, int, named_family, std::optional<output_span<int>>);
	ASSERT_IS_PARSER(Nam4, int, named_family, std::tuple<output_span<int>, std::vector<output_span<int>>>);
}

TEST("Named", "Named<all_of_parser>")
{
    ASSERT_PARSE_SUCCESS(Nam1, "abc", "abc", "");
    ASSERT_PARSE_SUCCESS(Nam1, "abcd", "abc", "d");
    ASSERT_PARSE_FAILURE(Nam1, " abc");

    ASSERT_PARSE_SUCCESS(Nam1, L"abc", L"abc", L"");
    ASSERT_PARSE_SUCCESS(Nam1, L"abcd", L"abc", L"d");
    ASSERT_PARSE_FAILURE(Nam1, L" abc");

    ASSERT_PARSE_SUCCESS(Nam1, e<int>("abc"), e<int>("abc"), e<int>(""));
    ASSERT_PARSE_SUCCESS(Nam1, e<int>("abcd"), e<int>("abc"), e<int>("d"));
    ASSERT_PARSE_FAILURE(Nam1, e<int>(" abc"));
}

TEST("Named", "Named<OneOrMore>")
{
    {
        using type = std::vector<output_span<char>>;
        ASSERT_PARSE_SUCCESS(Nam2, "abcabcab", (type{"abc", "abc"}), "ab");
        ASSERT_PARSE_SUCCESS(Nam2, "abcd", (type{"abc"}), "d");
        ASSERT_PARSE_SUCCESS(Nam2, "abc abc", (type{"abc"}), " abc");
        ASSERT_PARSE_FAILURE(Nam2, "ab abc");
        ASSERT_PARSE_FAILURE(Nam2, " ab abc");
    }
    
    {
        using type = std::vector<output_span<wchar_t>>;
        ASSERT_PARSE_SUCCESS(Nam2, L"abcabcab", (type{L"abc", L"abc"}), L"ab");
        ASSERT_PARSE_SUCCESS(Nam2, L"abcd", (type{L"abc"}), L"d");
        ASSERT_PARSE_SUCCESS(Nam2, L"abc abc", (type{L"abc"}), L" abc");
        ASSERT_PARSE_FAILURE(Nam2, L"ab abc");
        ASSERT_PARSE_FAILURE(Nam2, L" ab abc");
    }
    
    {
        using type = std::vector<output_span<int>>;
        ASSERT_PARSE_SUCCESS(Nam2, e<int>("abcabcab"), (type{e<int>("abc"), e<int>("abc")}), e<int>("ab"));
        ASSERT_PARSE_SUCCESS(Nam2, e<int>("abcd"), (type{e<int>("abc")}), e<int>("d"));
        ASSERT_PARSE_SUCCESS(Nam2, e<int>("abc abc"), (type{e<int>("abc")}), e<int>(" abc"));
        ASSERT_PARSE_FAILURE(Nam2, e<int>("ab abc"));
        ASSERT_PARSE_FAILURE(Nam2, e<int>(" ab abc"));
    }
}

TEST("Named", "Named<Maybe>")
{
    ASSERT_PARSE_SUCCESS(Nam3, "abcabcab", "abc", "abcab");
    ASSERT_PARSE_SUCCESS(Nam3, "abcd", "abc", "d");
    ASSERT_PARSE_SUCCESS(Nam3, "abc abc", "abc", " abc");
    ASSERT_PARSE_SUCCESS(Nam3, "ab abc", std::nullopt, "ab abc");
    ASSERT_PARSE_SUCCESS(Nam3, " ab abc", std::nullopt, " ab abc");
    ASSERT_PARSE_SUCCESS(Nam3, "?? ab abc", "??", " ab abc");
    ASSERT_PARSE_SUCCESS(Nam3, "??? ab abc", "??", "? ab abc");

    ASSERT_PARSE_SUCCESS(Nam3, L"abcabcab", L"abc", L"abcab");
    ASSERT_PARSE_SUCCESS(Nam3, L"abcd", L"abc", L"d");
    ASSERT_PARSE_SUCCESS(Nam3, L"abc abc", L"abc", L" abc");
    ASSERT_PARSE_SUCCESS(Nam3, L"ab abc", std::nullopt, L"ab abc");
    ASSERT_PARSE_SUCCESS(Nam3, L" ab abc", std::nullopt, L" ab abc");
    ASSERT_PARSE_SUCCESS(Nam3, L"?? ab abc", L"??", L" ab abc");
    ASSERT_PARSE_SUCCESS(Nam3, L"??? ab abc", L"??", L"? ab abc");

    ASSERT_PARSE_SUCCESS(Nam3, e<int>("abcabcab"), e<int>("abc"), e<int>("abcab"));
    ASSERT_PARSE_SUCCESS(Nam3, e<int>("abcd"), e<int>("abc"), e<int>("d"));
    ASSERT_PARSE_SUCCESS(Nam3, e<int>("abc abc"), e<int>("abc"), e<int>(" abc"));
    ASSERT_PARSE_SUCCESS(Nam3, e<int>("ab abc"), std::nullopt, e<int>("ab abc"));
    ASSERT_PARSE_SUCCESS(Nam3, e<int>(" ab abc"), std::nullopt, e<int>(" ab abc"));
    ASSERT_PARSE_SUCCESS(Nam3, e<int>("?? ab abc"), e<int>("??"), e<int>(" ab abc"));
    ASSERT_PARSE_SUCCESS(Nam3, e<int>("??? ab abc"), e<int>("??"), e<int>("? ab abc"));
}

TEST("Named", "Named<Sequence>")
{
    {
        using type = std::tuple<output_span<char>, std::vector<output_span<char>>>;
        ASSERT_PARSE_SUCCESS(Nam4, "abcabcab", (type{"abc", {}}), "abcab");
        ASSERT_PARSE_SUCCESS(Nam4, "abc?d", (type{"abc", {}}), "?d");
        ASSERT_PARSE_SUCCESS(Nam4, "abc???? abc", (type{"abc", {"??", "??"}}), " abc");
        ASSERT_PARSE_FAILURE(Nam4, "ab???? abc");
        ASSERT_PARSE_SUCCESS(Nam4, "abc?? ?? abc", (type{"abc", {"??"}}), " ?? abc");
    }
    
    {
        using type = std::tuple<output_span<wchar_t>, std::vector<output_span<wchar_t>>>;
        ASSERT_PARSE_SUCCESS(Nam4, L"abcabcab", (type{L"abc", {}}), L"abcab");
        ASSERT_PARSE_SUCCESS(Nam4, L"abc?d", (type{L"abc", {}}), L"?d");
        ASSERT_PARSE_SUCCESS(Nam4, L"abc???? abc", (type{L"abc", {L"??", L"??"}}), L" abc");
        ASSERT_PARSE_FAILURE(Nam4, L"ab???? abc");
        ASSERT_PARSE_SUCCESS(Nam4, L"abc?? ?? abc", (type{L"abc", {L"??"}}), L" ?? abc");
    }
    
    {
        using type = std::tuple<output_span<int>, std::vector<output_span<int>>>;
        ASSERT_PARSE_SUCCESS(Nam4, e<int>("abcabcab"), (type{e<int>("abc"), {}}), e<int>("abcab"));
        ASSERT_PARSE_SUCCESS(Nam4, e<int>("abc?d"), (type{e<int>("abc"), {}}), e<int>("?d"));
        ASSERT_PARSE_SUCCESS(Nam4, e<int>("abc???? abc"), (type{e<int>("abc"), {e<int>("??"), e<int>("??")}}), e<int>(" abc"));
        ASSERT_PARSE_FAILURE(Nam4, e<int>("ab???? abc"));
        ASSERT_PARSE_SUCCESS(Nam4, e<int>("abc?? ?? abc"), (type{e<int>("abc"), {e<int>("??")}}), e<int>(" ?? abc"));
    }
}
