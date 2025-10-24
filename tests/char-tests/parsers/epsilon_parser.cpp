// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("epsilon_parser");

TEST("epsilon_parser", "Requirements")
{
    EXPECT_THAT(the_parser<Eps1> | has_value_type<value_type>);
    EXPECT_THAT(the_parser<Eps1> | has_family<epsilon_family>);

    ASSERT_IS_PARSER(Eps1, char, epsilon_family, void);
    ASSERT_IS_PARSER(Eps1, wchar_t, epsilon_family, void);
    ASSERT_IS_PARSER(Eps1, int, epsilon_family, void);
}

TEST("epsilon_parser", "Parse")
{
    ASSERT_PARSE_SUCCESS_VOID(Eps1, "ab", "ab");
    ASSERT_PARSE_SUCCESS_VOID(Eps1, "ba", "ba");
    ASSERT_PARSE_SUCCESS_VOID(Eps1, "abc", "abc");
    ASSERT_PARSE_SUCCESS_VOID(Eps1, "Ab", "Ab");
    ASSERT_PARSE_SUCCESS_VOID(Eps1, "Abc", "Abc");
    ASSERT_PARSE_SUCCESS_VOID(Eps1, " abc", " abc");
    ASSERT_PARSE_SUCCESS_VOID(Eps1, "", "");

    ASSERT_PARSE_SUCCESS_VOID(Eps1, L"ab", L"ab");
    ASSERT_PARSE_SUCCESS_VOID(Eps1, L"ba", L"ba");
    ASSERT_PARSE_SUCCESS_VOID(Eps1, L"abc", L"abc");
    ASSERT_PARSE_SUCCESS_VOID(Eps1, L"Ab", L"Ab");
    ASSERT_PARSE_SUCCESS_VOID(Eps1, L"Abc", L"Abc");
    ASSERT_PARSE_SUCCESS_VOID(Eps1, L" abc", L" abc");
    ASSERT_PARSE_SUCCESS_VOID(Eps1, L"", L"");

    ASSERT_PARSE_SUCCESS_VOID(Eps1, e<int>("ab"), e<int>("ab"));
    ASSERT_PARSE_SUCCESS_VOID(Eps1, e<int>("ba"), e<int>("ba"));
    ASSERT_PARSE_SUCCESS_VOID(Eps1, e<int>("abc"), e<int>("abc"));
    ASSERT_PARSE_SUCCESS_VOID(Eps1, e<int>("Ab"), e<int>("Ab"));
    ASSERT_PARSE_SUCCESS_VOID(Eps1, e<int>("Abc"), e<int>("Abc"));
    ASSERT_PARSE_SUCCESS_VOID(Eps1, e<int>(" abc"), e<int>(" abc"));
    ASSERT_PARSE_SUCCESS_VOID(Eps1, e<int>(""), e<int>(""));
}

TEST("epsilon_parser", "choice_parser<P, epsilon_parser>")
{
    auto parser = TT("+-"_any_of) | eps;
    using P = decltype(parser);
    EXPECT_THAT(the_parser<P> | has_family<choice_family>);

    ASSERT_IS_PARSER(P, char, choice_family, output_span<char>);
    ASSERT_PARSE_SUCCESS(P, "+abc", "+", "abc");
    ASSERT_PARSE_SUCCESS(P, "++abc", "+", "+abc");
    ASSERT_PARSE_SUCCESS(P, "-abc", "-", "abc");
    ASSERT_PARSE_SUCCESS(P, "--abc", "-", "-abc");
    ASSERT_PARSE_SUCCESS(P, "abc", "", "abc");

    ASSERT_IS_PARSER(P, wchar_t, choice_family, output_span<wchar_t>);
    ASSERT_PARSE_SUCCESS(P, L"+abc", L"+", L"abc");
    ASSERT_PARSE_SUCCESS(P, L"++abc", L"+", L"+abc");
    ASSERT_PARSE_SUCCESS(P, L"-abc", L"-", L"abc");
    ASSERT_PARSE_SUCCESS(P, L"--abc", L"-", L"-abc");
    ASSERT_PARSE_SUCCESS(P, L"abc", L"", L"abc");

    ASSERT_IS_PARSER(P, int, choice_family, output_span<int>);
    ASSERT_PARSE_SUCCESS(P, e<int>("+abc"), e<int>("+"), e<int>("abc"));
    ASSERT_PARSE_SUCCESS(P, e<int>("++abc"), e<int>("+"), e<int>("+abc"));
    ASSERT_PARSE_SUCCESS(P, e<int>("-abc"), e<int>("-"), e<int>("abc"));
    ASSERT_PARSE_SUCCESS(P, e<int>("--abc"), e<int>("-"), e<int>("-abc"));
    ASSERT_PARSE_SUCCESS(P, e<int>("abc"), e<int>(""), e<int>("abc"));
}

} // namespace
} // namespace k3::tok3n::tests
