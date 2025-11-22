// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("not operator");

TEST("not operator", "!any_of_parser")
{
    EXPECT_THAT(parser_value<!any1>
                         .is<none1>);
    EXPECT_THAT(parser_value<!any2>
                         .is<none2>);
    EXPECT_THAT(parser_value<!any3>
                         .is<none3>);
    EXPECT_THAT(parser_value<!!any1>
                         .is<any1>);
    EXPECT_THAT(parser_value<!!any2>
                         .is<any2>);
    EXPECT_THAT(parser_value<!!any3>
                         .is<any3>);
}

TEST("not operator", "!none_of_parser")
{
    EXPECT_THAT(parser_value<!none1>
                         .is<any1>);
    EXPECT_THAT(parser_value<!none2>
                         .is<any2>);
    EXPECT_THAT(parser_value<!none3>
                         .is<any3>);
    EXPECT_THAT(parser_value<!!none1>
                         .is<none1>);
    EXPECT_THAT(parser_value<!!none2>
                         .is<none2>);
    EXPECT_THAT(parser_value<!!none3>
                         .is<none3>);
}

TEST("not operator", "non consteval")
{
    (!any1).parse(TT("abc"));
}



constexpr auto not_operator_fragment =
    []<detail::parser P>(P) {
        if constexpr (P::family == any_of_family)
        {
            constexpr bool cond1 = requires { { !P{} }-> k3::tok3n::detail::parser; };
            /* Workaround for Clang 16 */
            ASSERT_COMPILE_TIME(cond1);
            EXPECT_THAT(parser_value<!P{}>
                    .DEP_TEMPLATE is<none_of_parser<underlying_v<P>>{}>);
        }
        else if constexpr (P::family == none_of_family)
        {
            constexpr bool cond1 = requires { { !P{} }-> k3::tok3n::detail::parser; };
            /* Workaround for Clang 16 */
            ASSERT_COMPILE_TIME(cond1);
            EXPECT_THAT(parser_value<!P{}>
                    .DEP_TEMPLATE is<any_of_parser<underlying_v<P>>{}>);
        }
        else
        {
            ASSERT_COMPILE_TIME((not requires { !P{}; }));
        }
    };

TEST("not operator", "!{anything}")
{
    EXPECT_THAT(all_samples.satisfy(not_operator_fragment));
}

} // namespace
} // namespace k3::tok3n::tests
