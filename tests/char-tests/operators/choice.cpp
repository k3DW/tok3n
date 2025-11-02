// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("choice operator");

TEST("choice operator", "any_of_parser | any_of_parser")
{
    EXPECT_THAT(parser_value<any1 | any2>
                         .is<any2 | any1>);
    EXPECT_THAT(parser_value<any1 | any3>
                         .is<any3 | any1>);
    EXPECT_THAT(parser_value<any2 | any3>
                         .is<any3 | any2>);
    EXPECT_THAT(parser_value<any1 | any2>
                         .is<any_of_parser<TT("abcd")>{}>);
    EXPECT_THAT(parser_value<any1 | any3>
                         .is<any_of_parser<TT("abcxyz")>{}>);
    EXPECT_THAT(parser_value<any2 | any3>
                         .is<any_of_parser<TT("bcdxyz")>{}>);
    EXPECT_THAT(parser_value<any1 | any1>
                         .is<any1>);
    EXPECT_THAT(parser_value<any2 | any2>
                         .is<any2>);
    EXPECT_THAT(parser_value<any3 | any3>
                         .is<any3>);
}

TEST("choice operator", "none_of_parser | none_of_parser")
{
    EXPECT_THAT(parser_value<none1 | none2>
                         .is<none2 | none1>);
    EXPECT_THAT(parser_value<none1 | none3>
                         .is<none3 | none1>);
    EXPECT_THAT(parser_value<none2 | none3>
                         .is<none3 | none2>);
    EXPECT_THAT(parser_value<none1 | none2>
                         .is<none_of_parser<TT("bc")>{}>);
    EXPECT_THAT(parser_value<none1 | none3>
                         .is<none_of_parser<TT("")>{}>);
    EXPECT_THAT(parser_value<none2 | none3>
                         .is<none_of_parser<TT("")>{}>);
    EXPECT_THAT(parser_value<none1 | none1>
                         .is<none1>);
    EXPECT_THAT(parser_value<none2 | none2>
                         .is<none2>);
    EXPECT_THAT(parser_value<none3 | none3>
                         .is<none3>);
}

TEST("choice operator", "any_of_parser | none_of_parser, and none_of_parser | any_of_parser")
{
    EXPECT_THAT(parser_value<any1 | none1>
                         .is<none1 | any1>);
    EXPECT_THAT(parser_value<any1 | none2>
                         .is<none2 | any1>);
    EXPECT_THAT(parser_value<any1 | none3>
                         .is<none3 | any1>);
    EXPECT_THAT(parser_value<any2 | none1>
                         .is<none1 | any2>);
    EXPECT_THAT(parser_value<any2 | none2>
                         .is<none2 | any2>);
    EXPECT_THAT(parser_value<any2 | none3>
                         .is<none3 | any2>);
    EXPECT_THAT(parser_value<any3 | none1>
                         .is<none1 | any3>);
    EXPECT_THAT(parser_value<any3 | none2>
                         .is<none2 | any3>);
    EXPECT_THAT(parser_value<any3 | none3>
                         .is<none3 | any3>);
    EXPECT_THAT(parser_value<any1 | none1>
                         .is<none_of_parser<TT("")>{}>);
    EXPECT_THAT(parser_value<any1 | none2>
                         .is<none_of_parser<TT("d")>{}>);
    EXPECT_THAT(parser_value<any1 | none3>
                         .is<none_of_parser<TT("xyz")>{}>);
    EXPECT_THAT(parser_value<any2 | none1>
                         .is<none_of_parser<TT("a")>{}>);
    EXPECT_THAT(parser_value<any2 | none2>
                         .is<none_of_parser<TT("")>{}>);
    EXPECT_THAT(parser_value<any2 | none3>
                         .is<none_of_parser<TT("xyz")>{}>);
    EXPECT_THAT(parser_value<any3 | none1>
                         .is<none_of_parser<TT("abc")>{}>);
    EXPECT_THAT(parser_value<any3 | none2>
                         .is<none_of_parser<TT("bcd")>{}>);
    EXPECT_THAT(parser_value<any3 | none3>
                         .is<none_of_parser<TT("")>{}>);
}



TEST("choice operator", "choice_parser | choice_parser")
{
    EXPECT_THAT(parser_value<cho1 | cho1>
                         .is<cho1>);
    EXPECT_THAT(parser_value<cho2 | cho2>
                         .is<cho2>);
    EXPECT_THAT(parser_value<cho3 | cho3>
                         .is<cho3>);
    EXPECT_THAT(parser_value<cho4 | cho4>
                         .is<cho4>);
    EXPECT_THAT(parser_value<cho1 | cho2>
                         .is<(choice_parser<All4, Non4, Non4, All4>{})>);
    EXPECT_THAT(parser_value<cho2 | cho1>
                         .is<(choice_parser<Non4, All4, All4, Non4>{})>);
    EXPECT_THAT(parser_value<cho1 | cho3>
                         .is<(choice_parser<All4, Non4, All4, Any4, Non5>{})>);
    EXPECT_THAT(parser_value<cho3 | cho1>
                         .is<(choice_parser<All4, Any4, Non5, All4, Non4>{})>);
    EXPECT_THAT(parser_value<cho1 | cho4>
                         .is<(choice_parser<All4, Non4, Non5, All4, Any4>{})>);
    EXPECT_THAT(parser_value<cho4 | cho1>
                         .is<(choice_parser<Non5, All4, Any4, All4, Non4>{})>);
    EXPECT_THAT(parser_value<cho2 | cho3>
                         .is<(choice_parser<Non4, All4, All4, Any4, Non5>{})>);
    EXPECT_THAT(parser_value<cho3 | cho2>
                         .is<(choice_parser<All4, Any4, Non5, Non4, All4>{})>);
    EXPECT_THAT(parser_value<cho2 | cho4>
                         .is<(choice_parser<Non4, All4, Non5, All4, Any4>{})>);
    EXPECT_THAT(parser_value<cho4 | cho2>
                         .is<(choice_parser<Non5, All4, Any4, Non4, All4>{})>);
    EXPECT_THAT(parser_value<cho3 | cho4>
                         .is<(choice_parser<All4, Any4, Non5, Non5, All4, Any4>{})>);
    EXPECT_THAT(parser_value<cho4 | cho3>
                         .is<(choice_parser<Non5, All4, Any4, All4, Any4, Non5>{})>);
    EXPECT_THAT(parser_value<cho5 | cho5>
                         .is<cho5>);
}

TEST("choice operator", "choice_parser | {anything}, and {anything} | choice_parser")
{
    EXPECT_THAT(parser_value<cho1 | any1>
                         .is<(choice_parser<All4, Non4, Any1>{})>);
    EXPECT_THAT(parser_value<any1 | cho1>
                         .is<(choice_parser<Any1, All4, Non4>{})>);
    EXPECT_THAT(parser_value<cho2 | any4>
                         .is<(choice_parser<Non4, All4, Any4>{})>);
    EXPECT_THAT(parser_value<any4 | cho2>
                         .is<(choice_parser<Any4, Non4, All4>{})>);
    EXPECT_THAT(parser_value<cho3 | any3>
                         .is<(choice_parser<All4, Any4, Non5, Any3>{})>);
    EXPECT_THAT(parser_value<any3 | cho3>
                         .is<(choice_parser<Any3, All4, Any4, Non5>{})>);
    EXPECT_THAT(parser_value<cho4 | any2>
                         .is<(choice_parser<Non5, All4, Any4, Any2>{})>);
    EXPECT_THAT(parser_value<any2 | cho4>
                         .is<(choice_parser<Any2, Non5, All4, Any4>{})>);
}

TEST("choice operator", "void result_type")
{
    EXPECT_THAT(parser_value<ign1 | ign2>
                         .is<cho5>);
    EXPECT_THAT(parser_value<ign2 | ign1>
                     .is_not<cho5>);
}

TEST("choice operator", "non consteval")
{
    (any1 | any2).parse(TT("abc"));
}



#define CHOICE_OPERATOR_ASSERTER(LHS, RHS)                                                           \
    []<parser LLHS, parser RRHS>(LLHS, RRHS) {                                                       \
        if constexpr (not std::same_as<typename LLHS::value_type, typename RRHS::value_type>)        \
        {                                                                                            \
            ASSERT_COMPILE_TIME((not requires { LLHS{} | RRHS{}; }));                                \
        }                                                                                            \
        else                                                                                         \
        {                                                                                            \
            ASSERT_COMPILE_TIME((requires { { LLHS{} | RRHS{} } -> k3::tok3n::detail::parser; }));   \
            if constexpr (std::same_as<LLHS, RRHS>)                                                  \
            {                                                                                        \
                EXPECT_THAT(parser_value<LLHS{} | RRHS{}>.is<LLHS{}>);                               \
            }                                                                                        \
            else if constexpr (LLHS::family == any_of_family and RRHS::family == any_of_family)      \
            {                                                                                        \
                constexpr auto str = set_union<underlying_v<LLHS>, underlying_v<RRHS>>();            \
                EXPECT_THAT(parser_value<LLHS{} | RRHS{}>.is<any_of_parser<str>{}>);                 \
            }                                                                                        \
            else if constexpr (LLHS::family == none_of_family and RRHS::family == none_of_family)    \
            {                                                                                        \
                constexpr auto str = set_intersection<underlying_v<LLHS>, underlying_v<RRHS>>();     \
                EXPECT_THAT(parser_value<LLHS{} | RRHS{}>.is<none_of_parser<str>{}>);                \
            }                                                                                        \
            else if constexpr (LLHS::family == none_of_family and RRHS::family == any_of_family)     \
            {                                                                                        \
                constexpr auto str = set_difference_left<underlying_v<LLHS>, underlying_v<RRHS>>();  \
                EXPECT_THAT(parser_value<LLHS{} | RRHS{}>.is<none_of_parser<str>{}>);                \
            }                                                                                        \
            else if constexpr (LLHS::family == any_of_family and RRHS::family == none_of_family)     \
            {                                                                                        \
                constexpr auto str = set_difference_right<underlying_v<LLHS>, underlying_v<RRHS>>(); \
                EXPECT_THAT(parser_value<LLHS{} | RRHS{}>.is<none_of_parser<str>{}>);                \
            }                                                                                        \
            else if constexpr (LLHS::family == choice_family and RRHS::family != choice_family)      \
            {                                                                                        \
                EXPECT_THAT(parser_value<LLHS{} | RRHS{}>                                            \
                                     .is<choice_combined_left(LLHS{}, RRHS{})>);                     \
            }                                                                                        \
            else if constexpr (LLHS::family != choice_family and RRHS::family == choice_family)      \
            {                                                                                        \
                EXPECT_THAT(parser_value<LLHS{} | RRHS{}>                                            \
                                     .is<choice_combined_right(LLHS{}, RRHS{})>);                    \
            }                                                                                        \
            else if constexpr (LLHS::family == choice_family and RRHS::family == choice_family)      \
            {                                                                                        \
                EXPECT_THAT(parser_value<LLHS{} | RRHS{}>                                            \
                                     .is<choice_combined_both(LLHS{}, RRHS{})>);                     \
            }                                                                                        \
            else                                                                                     \
            {                                                                                        \
                EXPECT_THAT(parser_value<LLHS{} | RRHS{}>                                            \
                                     .is<(choice_parser<LLHS, RRHS>{})>);                            \
            }                                                                                        \
        }                                                                                            \
    }(LHS{}, RHS{});

#define CHOICE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES \
    (any_of_parser<"abc">) (any_of_parser<"xyz">) (any_of_parser<L"abc">) (any_of_parser<L"xyz">)

TEST("choice operator", "{anything} | {anything}")
{
    // Note that all the operations are reimplemented for choice_checker. This is intentional. That way, there's redundancy in the code.
    // A basic implementation is here, so if/when it gets changed in the library itself, it will be detected here.

    // This works just fine, but it takes forever and may crash your computer. User beware.
    // ASSERT_ALL_SAMPLES_2(CHOICE_OPERATOR_ASSERTER);

    ASSERT_SAMPLES_2(CHOICE_OPERATOR_ASSERTER, CHOICE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES, CHOICE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES);

    ASSERT_SAMPLES_2(CHOICE_OPERATOR_ASSERTER, BASIC_SAMPLES, BASIC_SAMPLES);
}

} // namespace
} // namespace k3::tok3n::tests
