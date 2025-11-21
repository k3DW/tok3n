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
    ASSERT_PARSE_SUCCESS_VOID(Ign1, "abcabc", "abc");
    EXPECT_THAT(the_parser<Ign1> | FAILS_PARSING("Abcabc"));
    EXPECT_THAT(the_parser<Ign1> | FAILS_PARSING(" abcabc"));

    ASSERT_PARSE_SUCCESS_VOID(Ign2, "abcabcabcab", "ab");
    EXPECT_THAT(the_parser<Ign2> | FAILS_PARSING(""));
    EXPECT_THAT(the_parser<Ign2> | FAILS_PARSING("ab"));
    ASSERT_PARSE_SUCCESS_VOID(Ign2, "abc", "");

    ASSERT_PARSE_SUCCESS_VOID(Ign3, "abcabc", "abc");
    ASSERT_PARSE_SUCCESS_VOID(Ign3, "a??bcabc", "a??bcabc");
    ASSERT_PARSE_SUCCESS_VOID(Ign3, "", "");
    ASSERT_PARSE_SUCCESS_VOID(Ign3, "??abcabc", "abcabc");
    ASSERT_PARSE_SUCCESS_VOID(Ign3, " ??abcabc", " ??abcabc");

    ASSERT_PARSE_SUCCESS_VOID(Ign4, "abc???????", "?");
    EXPECT_THAT(the_parser<Ign4> | FAILS_PARSING("??abc???????"));
    ASSERT_PARSE_SUCCESS_VOID(Ign4, "abc??abc???????", "abc???????");
    ASSERT_PARSE_SUCCESS_VOID(Ign4, "abc ??abc???????", " ??abc???????");
    EXPECT_THAT(the_parser<Ign4> | FAILS_PARSING(""));

    ASSERT_PARSE_SUCCESS_VOID(Ign5, "abcabcabcabc??", "");
    ASSERT_PARSE_SUCCESS_VOID(Ign5, "abcabcabcabc", "");
    ASSERT_PARSE_SUCCESS_VOID(Ign5, "abcabcabcabc ??", " ??");
    ASSERT_PARSE_SUCCESS_VOID(Ign5, "abc", "");
    EXPECT_THAT(the_parser<Ign5> | FAILS_PARSING(" abc"));
    EXPECT_THAT(the_parser<Ign5> | FAILS_PARSING(""));

    ASSERT_PARSE_SUCCESS_VOID(Ign1, L"abcabc", L"abc");
    EXPECT_THAT(the_parser<Ign1> | FAILS_PARSING(L"Abcabc"));
    EXPECT_THAT(the_parser<Ign1> | FAILS_PARSING(L" abcabc"));

    ASSERT_PARSE_SUCCESS_VOID(Ign2, L"abcabcabcab", L"ab");
    EXPECT_THAT(the_parser<Ign2> | FAILS_PARSING(L""));
    EXPECT_THAT(the_parser<Ign2> | FAILS_PARSING(L"ab"));
    ASSERT_PARSE_SUCCESS_VOID(Ign2, L"abc", L"");

    ASSERT_PARSE_SUCCESS_VOID(Ign3, L"abcabc", L"abc");
    ASSERT_PARSE_SUCCESS_VOID(Ign3, L"a??bcabc", L"a??bcabc");
    ASSERT_PARSE_SUCCESS_VOID(Ign3, L"", L"");
    ASSERT_PARSE_SUCCESS_VOID(Ign3, L"??abcabc", L"abcabc");
    ASSERT_PARSE_SUCCESS_VOID(Ign3, L" ??abcabc", L" ??abcabc");

    ASSERT_PARSE_SUCCESS_VOID(Ign4, L"abc???????", L"?");
    EXPECT_THAT(the_parser<Ign4> | FAILS_PARSING(L"??abc???????"));
    ASSERT_PARSE_SUCCESS_VOID(Ign4, L"abc??abc???????", L"abc???????");
    ASSERT_PARSE_SUCCESS_VOID(Ign4, L"abc ??abc???????", L" ??abc???????");
    EXPECT_THAT(the_parser<Ign4> | FAILS_PARSING(L""));

    ASSERT_PARSE_SUCCESS_VOID(Ign5, L"abcabcabcabc??", L"");
    ASSERT_PARSE_SUCCESS_VOID(Ign5, L"abcabcabcabc", L"");
    ASSERT_PARSE_SUCCESS_VOID(Ign5, L"abcabcabcabc ??", L" ??");
    ASSERT_PARSE_SUCCESS_VOID(Ign5, L"abc", L"");
    EXPECT_THAT(the_parser<Ign5> | FAILS_PARSING(L" abc"));
    EXPECT_THAT(the_parser<Ign5> | FAILS_PARSING(L""));

    ASSERT_PARSE_SUCCESS_VOID(Ign1, e<int>("abcabc"), e<int>("abc"));
    EXPECT_THAT(the_parser<Ign1> | FAILS_PARSING(e<int>("Abcabc")));
    EXPECT_THAT(the_parser<Ign1> | FAILS_PARSING(e<int>(" abcabc")));

    ASSERT_PARSE_SUCCESS_VOID(Ign2, e<int>("abcabcabcab"), e<int>("ab"));
    EXPECT_THAT(the_parser<Ign2> | FAILS_PARSING(e<int>()));
    EXPECT_THAT(the_parser<Ign2> | FAILS_PARSING(e<int>("ab")));
    ASSERT_PARSE_SUCCESS_VOID(Ign2, e<int>("abc"), e<int>());

    ASSERT_PARSE_SUCCESS_VOID(Ign3, e<int>("abcabc"), e<int>("abc"));
    ASSERT_PARSE_SUCCESS_VOID(Ign3, e<int>("a??bcabc"), e<int>("a??bcabc"));
    ASSERT_PARSE_SUCCESS_VOID(Ign3, e<int>(), e<int>());
    ASSERT_PARSE_SUCCESS_VOID(Ign3, e<int>("??abcabc"), e<int>("abcabc"));
    ASSERT_PARSE_SUCCESS_VOID(Ign3, e<int>(" ??abcabc"), e<int>(" ??abcabc"));

    ASSERT_PARSE_SUCCESS_VOID(Ign4, e<int>("abc???????"), e<int>("?"));
    EXPECT_THAT(the_parser<Ign4> | FAILS_PARSING(e<int>("??abc???????")));
    ASSERT_PARSE_SUCCESS_VOID(Ign4, e<int>("abc??abc???????"), e<int>("abc???????"));
    ASSERT_PARSE_SUCCESS_VOID(Ign4, e<int>("abc ??abc???????"), e<int>(" ??abc???????"));
    EXPECT_THAT(the_parser<Ign4> | FAILS_PARSING(e<int>()));

    ASSERT_PARSE_SUCCESS_VOID(Ign5, e<int>("abcabcabcabc??"), e<int>());
    ASSERT_PARSE_SUCCESS_VOID(Ign5, e<int>("abcabcabcabc"), e<int>());
    ASSERT_PARSE_SUCCESS_VOID(Ign5, e<int>("abcabcabcabc ??"), e<int>(" ??"));
    ASSERT_PARSE_SUCCESS_VOID(Ign5, e<int>("abc"), e<int>());
    EXPECT_THAT(the_parser<Ign5> | FAILS_PARSING(e<int>(" abc")));
    EXPECT_THAT(the_parser<Ign5> | FAILS_PARSING(e<int>()));
}

} // namespace
} // namespace k3::tok3n::tests
