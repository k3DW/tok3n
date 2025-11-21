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

    EXPECT_THAT(the_parser<Eps1> | is_parser_for<char>.with_result<void>);
    EXPECT_THAT(the_parser<Eps1> | is_parser_for<wchar_t>.with_result<void>);
    EXPECT_THAT(the_parser<Eps1> | is_parser_for<int>.with_result<void>);
}

TEST("epsilon_parser", "Parse")
{
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID("ab", "ab"));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID("ba", "ba"));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID("abc", "abc"));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID("Ab", "Ab"));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID("Abc", "Abc"));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(" abc", " abc"));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID("", ""));

    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(L"ab", L"ab"));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(L"ba", L"ba"));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(L"abc", L"abc"));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(L"Ab", L"Ab"));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(L"Abc", L"Abc"));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(L" abc", L" abc"));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(L"", L""));

    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e<int>("ab"), e<int>("ab")));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e<int>("ba"), e<int>("ba")));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e<int>("abc"), e<int>("abc")));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e<int>("Ab"), e<int>("Ab")));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e<int>("Abc"), e<int>("Abc")));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e<int>(" abc"), e<int>(" abc")));
    EXPECT_THAT(the_parser<Eps1> | SUCCEEDS_PARSING_VOID(e<int>(""), e<int>("")));
}

TEST("epsilon_parser", "choice_parser<P, epsilon_parser>")
{
    auto parser = TT("+-"_any_of) | eps;
    using P = decltype(parser);
    EXPECT_THAT(the_parser<P> | has_family<choice_family>);

    EXPECT_THAT(the_parser<P> | is_parser_for<char>.with_result<output_span<char>>);
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("+abc", "+", "abc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("++abc", "+", "+abc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("-abc", "-", "abc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("--abc", "-", "-abc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING("abc", "", "abc"));

    EXPECT_THAT(the_parser<P> | is_parser_for<wchar_t>.with_result<output_span<wchar_t>>);
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"+abc", L"+", L"abc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"++abc", L"+", L"+abc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"-abc", L"-", L"abc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"--abc", L"-", L"-abc"));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(L"abc", L"", L"abc"));

    EXPECT_THAT(the_parser<P> | is_parser_for<int>.with_result<output_span<int>>);
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("+abc"), e<int>("+"), e<int>("abc")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("++abc"), e<int>("+"), e<int>("+abc")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("-abc"), e<int>("-"), e<int>("abc")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("--abc"), e<int>("-"), e<int>("-abc")));
    EXPECT_THAT(the_parser<P> | SUCCEEDS_PARSING(e<int>("abc"), e<int>(""), e<int>("abc")));
}

} // namespace
} // namespace k3::tok3n::tests
