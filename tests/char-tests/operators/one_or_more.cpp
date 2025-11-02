// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("one_or_more operator");

TEST("one_or_more operator", "+maybe_parser")
{
    EXPECT_THAT(parser_value<+may1>
                         .is<zom1>);
    EXPECT_THAT(parser_value<+ +may1>
                         .is<zom1>);
    EXPECT_THAT(parser_value<+ + +may1>
                         .is<zom1>);
    EXPECT_THAT(parser_value<+may2>
                         .is<zom2>);
    EXPECT_THAT(parser_value<+ +may2>
                         .is<zom2>);
    EXPECT_THAT(parser_value<+ + +may2>
                         .is<zom2>);
    EXPECT_THAT(parser_value<+may3>
                         .is<zom3>);
    EXPECT_THAT(parser_value<+ +may3>
                         .is<zom3>);
    EXPECT_THAT(parser_value<+ + +may3>
                         .is<zom3>);
    EXPECT_THAT(parser_value<+may4>
                         .is<zom4>);
    EXPECT_THAT(parser_value<+ +may4>
                         .is<zom4>);
    EXPECT_THAT(parser_value<+ + +may4>
                         .is<zom4>);
}

TEST("one_or_more operator", "+one_or_more_parser")
{
    EXPECT_THAT(parser_value<+oom1>
                         .is<oom1>);
    EXPECT_THAT(parser_value<+ +oom1>
                         .is<oom1>);
    EXPECT_THAT(parser_value<+ + +oom1>
                         .is<oom1>);
    EXPECT_THAT(parser_value<+oom2>
                         .is<oom2>);
    EXPECT_THAT(parser_value<+ +oom2>
                         .is<oom2>);
    EXPECT_THAT(parser_value<+ + +oom2>
                         .is<oom2>);
    EXPECT_THAT(parser_value<+oom3>
                         .is<oom3>);
    EXPECT_THAT(parser_value<+ +oom3>
                         .is<oom3>);
    EXPECT_THAT(parser_value<+ + +oom3>
                         .is<oom3>);
    EXPECT_THAT(parser_value<+oom4>
                         .is<oom4>);
    EXPECT_THAT(parser_value<+ +oom4>
                         .is<oom4>);
    EXPECT_THAT(parser_value<+ + +oom4>
                         .is<oom4>);
}

TEST("one_or_more operator", "+zero_or_more_parser")
{
    EXPECT_THAT(parser_value<+zom1>
                         .is<zom1>);
    EXPECT_THAT(parser_value<+ +zom1>
                         .is<zom1>);
    EXPECT_THAT(parser_value<+ + +zom1>
                         .is<zom1>);
    EXPECT_THAT(parser_value<+zom2>
                         .is<zom2>);
    EXPECT_THAT(parser_value<+ +zom2>
                         .is<zom2>);
    EXPECT_THAT(parser_value<+ + +zom2>
                         .is<zom2>);
    EXPECT_THAT(parser_value<+zom3>
                         .is<zom3>);
    EXPECT_THAT(parser_value<+ +zom3>
                         .is<zom3>);
    EXPECT_THAT(parser_value<+ + +zom3>
                         .is<zom3>);
    EXPECT_THAT(parser_value<+zom4>
                         .is<zom4>);
    EXPECT_THAT(parser_value<+ +zom4>
                         .is<zom4>);
    EXPECT_THAT(parser_value<+ + +zom4>
                         .is<zom4>);
}

TEST("one_or_more operator", "non consteval")
{
    (+any1).parse(TT("abc"));
}



#define ONE_OR_MORE_OPERATOR_ASSERTER(P)                                             \
    []<parser PP>(PP) {                                                              \
        ASSERT_COMPILE_TIME((requires { { +PP{} } -> k3::tok3n::detail::parser; })); \
        if constexpr (PP::family == maybe_family)                                    \
        {                                                                            \
            EXPECT_THAT(parser_value<+PP{}>                                          \
                    .DEP_TEMPLATE is<zero_or_more_parser<underlying_t<PP>>{}>);      \
        }                                                                            \
        else if constexpr (PP::family == one_or_more_family)                         \
        {                                                                            \
            EXPECT_THAT(parser_value<+PP{}>.DEP_TEMPLATE is<PP{}>);                  \
        }                                                                            \
        else if constexpr (PP::family == zero_or_more_family)                        \
        {                                                                            \
            EXPECT_THAT(parser_value<+PP{}>.DEP_TEMPLATE is<PP{}>);                  \
        }                                                                            \
        else                                                                         \
        {                                                                            \
            EXPECT_THAT(parser_value<+PP{}>                                          \
                    .DEP_TEMPLATE is<one_or_more_parser<PP>{}>);                     \
        }                                                                            \
    }(P{});

TEST("one_or_more operator", "+{anything}")
{
    ASSERT_ALL_SAMPLES(ONE_OR_MORE_OPERATOR_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
