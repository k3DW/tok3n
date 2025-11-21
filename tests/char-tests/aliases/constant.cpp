// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("constant_parser");

TEST("constant_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Con1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Con2> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Con3> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Con4> | has_value_type<value_type>);

    EXPECT_THAT(the_parser<Con1> | has_family<map_family>);
    EXPECT_THAT(the_parser<Con2> | has_family<map_family>);
    EXPECT_THAT(the_parser<Con3> | has_family<map_family>);
    EXPECT_THAT(the_parser<Con4> | has_family<map_family>);

    EXPECT_THAT(the_parser<Con1> | is_parser_for<char>.with_result<int>);
    EXPECT_THAT(the_parser<Con2> | is_parser_for<char>.with_result<char>);
    EXPECT_THAT(the_parser<Con3> | is_parser_for<char>.with_result<bool>);
    EXPECT_THAT(the_parser<Con4> | is_parser_for<char>.with_result<std::nullptr_t>);

    EXPECT_THAT(the_parser<Con1> | is_parser_for<wchar_t>.with_result<int>);
    EXPECT_THAT(the_parser<Con2> | is_parser_for<wchar_t>.with_result<char>);
    EXPECT_THAT(the_parser<Con3> | is_parser_for<wchar_t>.with_result<bool>);
    EXPECT_THAT(the_parser<Con4> | is_parser_for<wchar_t>.with_result<std::nullptr_t>);

    EXPECT_THAT(the_parser<Con1> | is_parser_for<int>.with_result<int>);
    EXPECT_THAT(the_parser<Con2> | is_parser_for<int>.with_result<char>);
    EXPECT_THAT(the_parser<Con3> | is_parser_for<int>.with_result<bool>);
    EXPECT_THAT(the_parser<Con4> | is_parser_for<int>.with_result<std::nullptr_t>);
}

TEST("constant_parser", "Parse all")
{
    EXPECT_THAT(the_parser<Con1> | SUCCEEDS_PARSING("abcabcabcab", 1, "ab"));
    ASSERT_PARSE_FAILURE(Con1, "");
    ASSERT_PARSE_FAILURE(Con1, "ab");
    EXPECT_THAT(the_parser<Con1> | SUCCEEDS_PARSING("abc", 1, ""));

    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING("abcabc", 't', "abc"));
    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING("a??bcabc", 't', "a??bcabc"));
    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING("", 't', ""));
    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING("??abcabc", 't', "abcabc"));
    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING(" ??abcabc", 't', " ??abcabc"));

    EXPECT_THAT(the_parser<Con3> | SUCCEEDS_PARSING("abc???????", true, "?"));
    ASSERT_PARSE_FAILURE(Con3, "??abc???????");
    EXPECT_THAT(the_parser<Con3> | SUCCEEDS_PARSING("abc??abc???????", true, "abc???????"));
    EXPECT_THAT(the_parser<Con3> | SUCCEEDS_PARSING("abc ??abc???????", true, " ??abc???????"));
    ASSERT_PARSE_FAILURE(Con3, "");

    EXPECT_THAT(the_parser<Con4> | SUCCEEDS_PARSING("abcabcabcabc??", nullptr, ""));
    EXPECT_THAT(the_parser<Con4> | SUCCEEDS_PARSING("abcabcabcabc", nullptr, ""));
    EXPECT_THAT(the_parser<Con4> | SUCCEEDS_PARSING("abcabcabcabc ??", nullptr, " ??"));
    EXPECT_THAT(the_parser<Con4> | SUCCEEDS_PARSING("abc", nullptr, ""));
    ASSERT_PARSE_FAILURE(Con4, " abc");
    ASSERT_PARSE_FAILURE(Con4, "");

    EXPECT_THAT(the_parser<Con1> | SUCCEEDS_PARSING(L"abcabcabcab", 1, L"ab"));
    ASSERT_PARSE_FAILURE(Con1, L"");
    ASSERT_PARSE_FAILURE(Con1, L"ab");
    EXPECT_THAT(the_parser<Con1> | SUCCEEDS_PARSING(L"abc", 1, L""));

    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING(L"abcabc", 't', L"abc"));
    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING(L"a??bcabc", 't', L"a??bcabc"));
    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING(L"", 't', L""));
    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING(L"??abcabc", 't', L"abcabc"));
    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING(L" ??abcabc", 't', L" ??abcabc"));

    EXPECT_THAT(the_parser<Con3> | SUCCEEDS_PARSING(L"abc???????", true, L"?"));
    ASSERT_PARSE_FAILURE(Con3, L"??abc???????");
    EXPECT_THAT(the_parser<Con3> | SUCCEEDS_PARSING(L"abc??abc???????", true, L"abc???????"));
    EXPECT_THAT(the_parser<Con3> | SUCCEEDS_PARSING(L"abc ??abc???????", true, L" ??abc???????"));
    ASSERT_PARSE_FAILURE(Con3, L"");

    EXPECT_THAT(the_parser<Con4> | SUCCEEDS_PARSING(L"abcabcabcabc??", nullptr, L""));
    EXPECT_THAT(the_parser<Con4> | SUCCEEDS_PARSING(L"abcabcabcabc", nullptr, L""));
    EXPECT_THAT(the_parser<Con4> | SUCCEEDS_PARSING(L"abcabcabcabc ??", nullptr, L" ??"));
    EXPECT_THAT(the_parser<Con4> | SUCCEEDS_PARSING(L"abc", nullptr, L""));
    ASSERT_PARSE_FAILURE(Con4, L" abc");
    ASSERT_PARSE_FAILURE(Con4, L"");

    EXPECT_THAT(the_parser<Con1> | SUCCEEDS_PARSING(e<int>("abcabcabcab"), 1, e<int>("ab")));
    ASSERT_PARSE_FAILURE(Con1, e<int>(""));
    ASSERT_PARSE_FAILURE(Con1, e<int>("ab"));
    EXPECT_THAT(the_parser<Con1> | SUCCEEDS_PARSING(e<int>("abc"), 1, e<int>("")));

    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING(e<int>("abcabc"), 't', e<int>("abc")));
    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING(e<int>("a??bcabc"), 't', e<int>("a??bcabc")));
    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING(e<int>(""), 't', e<int>("")));
    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING(e<int>("??abcabc"), 't', e<int>("abcabc")));
    EXPECT_THAT(the_parser<Con2> | SUCCEEDS_PARSING(e<int>(" ??abcabc"), 't', e<int>(" ??abcabc")));

    EXPECT_THAT(the_parser<Con3> | SUCCEEDS_PARSING(e<int>("abc???????"), true, e<int>("?")));
    ASSERT_PARSE_FAILURE(Con3, e<int>("??abc???????"));
    EXPECT_THAT(the_parser<Con3> | SUCCEEDS_PARSING(e<int>("abc??abc???????"), true, e<int>("abc???????")));
    EXPECT_THAT(the_parser<Con3> | SUCCEEDS_PARSING(e<int>("abc ??abc???????"), true, e<int>(" ??abc???????")));
    ASSERT_PARSE_FAILURE(Con3, e<int>(""));

    EXPECT_THAT(the_parser<Con4> | SUCCEEDS_PARSING(e<int>("abcabcabcabc??"), nullptr, e<int>("")));
    EXPECT_THAT(the_parser<Con4> | SUCCEEDS_PARSING(e<int>("abcabcabcabc"), nullptr, e<int>("")));
    EXPECT_THAT(the_parser<Con4> | SUCCEEDS_PARSING(e<int>("abcabcabcabc ??"), nullptr, e<int>(" ??")));
    EXPECT_THAT(the_parser<Con4> | SUCCEEDS_PARSING(e<int>("abc"), nullptr, e<int>("")));
    ASSERT_PARSE_FAILURE(Con4, e<int>(" abc"));
    ASSERT_PARSE_FAILURE(Con4, e<int>(""));
}

} // namespace
} // namespace k3::tok3n::tests
