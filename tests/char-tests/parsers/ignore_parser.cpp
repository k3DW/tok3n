// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("ignore_parser");

TEST("ignore_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Ign1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Ign2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Ign3> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Ign4> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Ign5> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Ign1> | has_family<ignore_family>);
    EXPECT_THAT(the_parser<Ign2> | has_family<ignore_family>);
    EXPECT_THAT(the_parser<Ign3> | has_family<ignore_family>);
    EXPECT_THAT(the_parser<Ign4> | has_family<ignore_family>);
    EXPECT_THAT(the_parser<Ign5> | has_family<ignore_family>);

    EXPECT_THAT(the_parser<Ign1> | is_parser_for<char>.with_result<void>);
    EXPECT_THAT(the_parser<Ign2> | is_parser_for<char>.with_result<void>);
    EXPECT_THAT(the_parser<Ign3> | is_parser_for<char>.with_result<void>);
    EXPECT_THAT(the_parser<Ign4> | is_parser_for<char>.with_result<void>);
    EXPECT_THAT(the_parser<Ign5> | is_parser_for<char>.with_result<void>);

    EXPECT_THAT(the_parser<Ign1> | is_parser_for<wchar_t>.with_result<void>);
    EXPECT_THAT(the_parser<Ign2> | is_parser_for<wchar_t>.with_result<void>);
    EXPECT_THAT(the_parser<Ign3> | is_parser_for<wchar_t>.with_result<void>);
    EXPECT_THAT(the_parser<Ign4> | is_parser_for<wchar_t>.with_result<void>);
    EXPECT_THAT(the_parser<Ign5> | is_parser_for<wchar_t>.with_result<void>);

    EXPECT_THAT(the_parser<Ign1> | is_parser_for<int>.with_result<void>);
    EXPECT_THAT(the_parser<Ign2> | is_parser_for<int>.with_result<void>);
    EXPECT_THAT(the_parser<Ign3> | is_parser_for<int>.with_result<void>);
    EXPECT_THAT(the_parser<Ign4> | is_parser_for<int>.with_result<void>);
    EXPECT_THAT(the_parser<Ign5> | is_parser_for<int>.with_result<void>);
}

TEST("ignore_parser", "Parse all")
{
    EXPECT_THAT(the_parser<Ign1> | SUCCEEDS_PARSING_VOID("abcabc", "abc"));
    EXPECT_THAT(the_parser<Ign1> | FAILS_PARSING("Abcabc"));
    EXPECT_THAT(the_parser<Ign1> | FAILS_PARSING(" abcabc"));

    EXPECT_THAT(the_parser<Ign2> | SUCCEEDS_PARSING_VOID("abcabcabcab", "ab"));
    EXPECT_THAT(the_parser<Ign2> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Ign2> | FAILS_PARSING("ab"));
    EXPECT_THAT(the_parser<Ign2> | SUCCEEDS_PARSING_VOID("abc", ""));

    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID("abcabc", "abc"));
    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID("a??bcabc", "a??bcabc"));
    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID("", ""));
    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID("??abcabc", "abcabc"));
    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID(" ??abcabc", " ??abcabc"));

    EXPECT_THAT(the_parser<Ign4> | SUCCEEDS_PARSING_VOID("abc???????", "?"));
    EXPECT_THAT(the_parser<Ign4> | FAILS_PARSING("??abc???????"));
    EXPECT_THAT(the_parser<Ign4> | SUCCEEDS_PARSING_VOID("abc??abc???????", "abc???????"));
    EXPECT_THAT(the_parser<Ign4> | SUCCEEDS_PARSING_VOID("abc ??abc???????", " ??abc???????"));
    EXPECT_THAT(the_parser<Ign4> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Ign5> | SUCCEEDS_PARSING_VOID("abcabcabcabc??", ""));
    EXPECT_THAT(the_parser<Ign5> | SUCCEEDS_PARSING_VOID("abcabcabcabc", ""));
    EXPECT_THAT(the_parser<Ign5> | SUCCEEDS_PARSING_VOID("abcabcabcabc ??", " ??"));
    EXPECT_THAT(the_parser<Ign5> | SUCCEEDS_PARSING_VOID("abc", ""));
    EXPECT_THAT(the_parser<Ign5> | FAILS_PARSING(" abc"));
    EXPECT_THAT(the_parser<Ign5> | FAILS_PARSING(""));

    EXPECT_THAT(the_parser<Ign1> | SUCCEEDS_PARSING_VOID(L"abcabc", L"abc"));
    EXPECT_THAT(the_parser<Ign1> | FAILS_PARSING(L"Abcabc"));
    EXPECT_THAT(the_parser<Ign1> | FAILS_PARSING(L" abcabc"));

    EXPECT_THAT(the_parser<Ign2> | SUCCEEDS_PARSING_VOID(L"abcabcabcab", L"ab"));
    EXPECT_THAT(the_parser<Ign2> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Ign2> | FAILS_PARSING(L"ab"));
    EXPECT_THAT(the_parser<Ign2> | SUCCEEDS_PARSING_VOID(L"abc", L""));

    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID(L"abcabc", L"abc"));
    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID(L"a??bcabc", L"a??bcabc"));
    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID(L"", L""));
    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID(L"??abcabc", L"abcabc"));
    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID(L" ??abcabc", L" ??abcabc"));

    EXPECT_THAT(the_parser<Ign4> | SUCCEEDS_PARSING_VOID(L"abc???????", L"?"));
    EXPECT_THAT(the_parser<Ign4> | FAILS_PARSING(L"??abc???????"));
    EXPECT_THAT(the_parser<Ign4> | SUCCEEDS_PARSING_VOID(L"abc??abc???????", L"abc???????"));
    EXPECT_THAT(the_parser<Ign4> | SUCCEEDS_PARSING_VOID(L"abc ??abc???????", L" ??abc???????"));
    EXPECT_THAT(the_parser<Ign4> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Ign5> | SUCCEEDS_PARSING_VOID(L"abcabcabcabc??", L""));
    EXPECT_THAT(the_parser<Ign5> | SUCCEEDS_PARSING_VOID(L"abcabcabcabc", L""));
    EXPECT_THAT(the_parser<Ign5> | SUCCEEDS_PARSING_VOID(L"abcabcabcabc ??", L" ??"));
    EXPECT_THAT(the_parser<Ign5> | SUCCEEDS_PARSING_VOID(L"abc", L""));
    EXPECT_THAT(the_parser<Ign5> | FAILS_PARSING(L" abc"));
    EXPECT_THAT(the_parser<Ign5> | FAILS_PARSING(L""));

    EXPECT_THAT(the_parser<Ign1> | SUCCEEDS_PARSING_VOID(e<int>("abcabc"), e<int>("abc")));
    EXPECT_THAT(the_parser<Ign1> | FAILS_PARSING(e<int>("Abcabc")));
    EXPECT_THAT(the_parser<Ign1> | FAILS_PARSING(e<int>(" abcabc")));

    EXPECT_THAT(the_parser<Ign2> | SUCCEEDS_PARSING_VOID(e<int>("abcabcabcab"), e<int>("ab")));
    EXPECT_THAT(the_parser<Ign2> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Ign2> | FAILS_PARSING(e<int>("ab")));
    EXPECT_THAT(the_parser<Ign2> | SUCCEEDS_PARSING_VOID(e<int>("abc"), e<int>()));

    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID(e<int>("abcabc"), e<int>("abc")));
    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID(e<int>("a??bcabc"), e<int>("a??bcabc")));
    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID(e<int>(), e<int>()));
    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID(e<int>("??abcabc"), e<int>("abcabc")));
    EXPECT_THAT(the_parser<Ign3> | SUCCEEDS_PARSING_VOID(e<int>(" ??abcabc"), e<int>(" ??abcabc")));

    EXPECT_THAT(the_parser<Ign4> | SUCCEEDS_PARSING_VOID(e<int>("abc???????"), e<int>("?")));
    EXPECT_THAT(the_parser<Ign4> | FAILS_PARSING(e<int>("??abc???????")));
    EXPECT_THAT(the_parser<Ign4> | SUCCEEDS_PARSING_VOID(e<int>("abc??abc???????"), e<int>("abc???????")));
    EXPECT_THAT(the_parser<Ign4> | SUCCEEDS_PARSING_VOID(e<int>("abc ??abc???????"), e<int>(" ??abc???????")));
    EXPECT_THAT(the_parser<Ign4> | FAILS_PARSING(e<int>()));

    EXPECT_THAT(the_parser<Ign5> | SUCCEEDS_PARSING_VOID(e<int>("abcabcabcabc??"), e<int>()));
    EXPECT_THAT(the_parser<Ign5> | SUCCEEDS_PARSING_VOID(e<int>("abcabcabcabc"), e<int>()));
    EXPECT_THAT(the_parser<Ign5> | SUCCEEDS_PARSING_VOID(e<int>("abcabcabcabc ??"), e<int>(" ??")));
    EXPECT_THAT(the_parser<Ign5> | SUCCEEDS_PARSING_VOID(e<int>("abc"), e<int>()));
    EXPECT_THAT(the_parser<Ign5> | FAILS_PARSING(e<int>(" abc")));
    EXPECT_THAT(the_parser<Ign5> | FAILS_PARSING(e<int>()));
}

} // namespace
} // namespace k3::tok3n::tests
