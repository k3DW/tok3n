// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("maybe operator");

TEST("maybe operator", "~maybe_parser")
{
    EXPECT_THAT(parser_value<~may1>
                         .is<may1>);
    EXPECT_THAT(parser_value<~~may1>
                         .is<may1>);
    EXPECT_THAT(parser_value<~~~may1>
                         .is<may1>);
    EXPECT_THAT(parser_value<~may2>
                         .is<may2>);
    EXPECT_THAT(parser_value<~~may2>
                         .is<may2>);
    EXPECT_THAT(parser_value<~~~may2>
                         .is<may2>);
    EXPECT_THAT(parser_value<~may3>
                         .is<may3>);
    EXPECT_THAT(parser_value<~~may3>
                         .is<may3>);
    EXPECT_THAT(parser_value<~~~may3>
                         .is<may3>);
    EXPECT_THAT(parser_value<~may4>
                         .is<may4>);
    EXPECT_THAT(parser_value<~~may4>
                         .is<may4>);
    EXPECT_THAT(parser_value<~~~may4>
                         .is<may4>);
}

TEST("maybe operator", "~one_or_more_parser")
{
    EXPECT_THAT(parser_value<~oom1>
                         .is<zom1>);
    EXPECT_THAT(parser_value<~~oom1>
                         .is<zom1>);
    EXPECT_THAT(parser_value<~~~oom1>
                         .is<zom1>);
    EXPECT_THAT(parser_value<~oom2>
                         .is<zom2>);
    EXPECT_THAT(parser_value<~~oom2>
                         .is<zom2>);
    EXPECT_THAT(parser_value<~~~oom2>
                         .is<zom2>);
    EXPECT_THAT(parser_value<~oom3>
                         .is<zom3>);
    EXPECT_THAT(parser_value<~~oom3>
                         .is<zom3>);
    EXPECT_THAT(parser_value<~~~oom3>
                         .is<zom3>);
    EXPECT_THAT(parser_value<~oom4>
                         .is<zom4>);
    EXPECT_THAT(parser_value<~~oom4>
                         .is<zom4>);
    EXPECT_THAT(parser_value<~~~oom4>
                         .is<zom4>);
}

TEST("maybe operator", "~zero_or_more_parser")
{
    EXPECT_THAT(parser_value<~zom1>
                         .is<zom1>);
    EXPECT_THAT(parser_value<~~zom1>
                         .is<zom1>);
    EXPECT_THAT(parser_value<~~~zom1>
                         .is<zom1>);
    EXPECT_THAT(parser_value<~zom2>
                         .is<zom2>);
    EXPECT_THAT(parser_value<~~zom2>
                         .is<zom2>);
    EXPECT_THAT(parser_value<~~~zom2>
                         .is<zom2>);
    EXPECT_THAT(parser_value<~zom3>
                         .is<zom3>);
    EXPECT_THAT(parser_value<~~zom3>
                         .is<zom3>);
    EXPECT_THAT(parser_value<~~~zom3>
                         .is<zom3>);
    EXPECT_THAT(parser_value<~zom4>
                         .is<zom4>);
    EXPECT_THAT(parser_value<~~zom4>
                         .is<zom4>);
    EXPECT_THAT(parser_value<~~~zom4>
                         .is<zom4>);
}

TEST("maybe operator", "non consteval")
{
    (~any1).parse(TT("abc"));
}



#define MAYBE_OPERATOR_ASSERTER(P)                                                   \
    []<parser PP>(PP) {                                                              \
        ASSERT_COMPILE_TIME((requires { { ~PP{} } -> k3::tok3n::detail::parser; })); \
        if constexpr (PP::family == maybe_family)                                    \
        {                                                                            \
            EXPECT_THAT(parser_value<~PP{}>.is<PP{}>);                               \
        }                                                                            \
        else if constexpr (PP::family == one_or_more_family)                         \
        {                                                                            \
            EXPECT_THAT(parser_value<~PP{}>                                          \
                                 .is<zero_or_more_parser<underlying_t<PP>>{}>);      \
        }                                                                            \
        else if constexpr (PP::family == zero_or_more_family)                        \
        {                                                                            \
            EXPECT_THAT(parser_value<~PP{}>.is<PP{}>);                               \
        }                                                                            \
        else                                                                         \
        {                                                                            \
            EXPECT_THAT(parser_value<~PP{}>.is<maybe_parser<PP>{}>);                 \
        }                                                                            \
    }(P{});

TEST("maybe operator", "~{anything}")
{
    ASSERT_ALL_SAMPLES(MAYBE_OPERATOR_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
