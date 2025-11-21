// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("defaulted_parser");

TEST("defaulted_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Def1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Def2> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Def1> | has_family<map_family>);
    EXPECT_THAT(the_parser<Def2> | has_family<map_family>);

    EXPECT_THAT(the_parser<Def1> | is_parser_for<char>.with_result<int>);
    EXPECT_THAT(the_parser<Def2> | is_parser_for<char>.with_result<Class3>);

    EXPECT_THAT(the_parser<Def1> | is_parser_for<wchar_t>.with_result<int>);
    EXPECT_THAT(the_parser<Def2> | is_parser_for<wchar_t>.with_result<Class3>);

    EXPECT_THAT(the_parser<Def1> | is_parser_for<int>.with_result<int>);
    EXPECT_THAT(the_parser<Def2> | is_parser_for<int>.with_result<Class3>);
}

TEST("defaulted_parser", "Parse all")
{
    EXPECT_THAT(the_parser<Def1> | SUCCEEDS_PARSING("abcabcabcab", 0, "ab"));
    ASSERT_PARSE_FAILURE(Def1, "");
    ASSERT_PARSE_FAILURE(Def1, "ab");
    EXPECT_THAT(the_parser<Def1> | SUCCEEDS_PARSING("abc", 0, ""));

    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING("abcabc", Class3{}, "abc"));
    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING("a??bcabc", Class3{}, "a??bcabc"));
    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING("", Class3{}, ""));
    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING("??abcabc", Class3{}, "abcabc"));
    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING(" ??abcabc", Class3{}, " ??abcabc"));

    EXPECT_THAT(the_parser<Def1> | SUCCEEDS_PARSING(L"abcabcabcab", 0, L"ab"));
    ASSERT_PARSE_FAILURE(Def1, L"");
    ASSERT_PARSE_FAILURE(Def1, L"ab");
    EXPECT_THAT(the_parser<Def1> | SUCCEEDS_PARSING(L"abc", 0, L""));

    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING(L"abcabc", Class3{}, L"abc"));
    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING(L"a??bcabc", Class3{}, L"a??bcabc"));
    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING(L"", Class3{}, L""));
    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING(L"??abcabc", Class3{}, L"abcabc"));
    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING(L" ??abcabc", Class3{}, L" ??abcabc"));

    EXPECT_THAT(the_parser<Def1> | SUCCEEDS_PARSING(e<int>("abcabcabcab"), 0, e<int>("ab")));
    ASSERT_PARSE_FAILURE(Def1, e<int>(""));
    ASSERT_PARSE_FAILURE(Def1, e<int>("ab"));
    EXPECT_THAT(the_parser<Def1> | SUCCEEDS_PARSING(e<int>("abc"), 0, e<int>("")));

    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING(e<int>("abcabc"), Class3{}, e<int>("abc")));
    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING(e<int>("a??bcabc"), Class3{}, e<int>("a??bcabc")));
    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING(e<int>(""), Class3{}, e<int>("")));
    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING(e<int>("??abcabc"), Class3{}, e<int>("abcabc")));
    EXPECT_THAT(the_parser<Def2> | SUCCEEDS_PARSING(e<int>(" ??abcabc"), Class3{}, e<int>(" ??abcabc")));
}

} // namespace
} // namespace k3::tok3n::tests
