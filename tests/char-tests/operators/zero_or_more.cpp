// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("zero_or_more operator");

TEST("zero_or_more operator", "*maybe_parser")
{
    ASSERT_PARSER_VALUES_EQ(*may1, zom1);
    ASSERT_PARSER_VALUES_EQ(**may1, zom1);
    ASSERT_PARSER_VALUES_EQ(***may1, zom1);
    ASSERT_PARSER_VALUES_EQ(*may2, zom2);
    ASSERT_PARSER_VALUES_EQ(**may2, zom2);
    ASSERT_PARSER_VALUES_EQ(***may2, zom2);
    ASSERT_PARSER_VALUES_EQ(*may3, zom3);
    ASSERT_PARSER_VALUES_EQ(**may3, zom3);
    ASSERT_PARSER_VALUES_EQ(***may3, zom3);
    ASSERT_PARSER_VALUES_EQ(*may4, zom4);
    ASSERT_PARSER_VALUES_EQ(**may4, zom4);
    ASSERT_PARSER_VALUES_EQ(***may4, zom4);
}

TEST("zero_or_more operator", "*one_or_more_parser")
{
    ASSERT_PARSER_VALUES_EQ(*oom1, zom1);
    ASSERT_PARSER_VALUES_EQ(**oom1, zom1);
    ASSERT_PARSER_VALUES_EQ(***oom1, zom1);
    ASSERT_PARSER_VALUES_EQ(*oom2, zom2);
    ASSERT_PARSER_VALUES_EQ(**oom2, zom2);
    ASSERT_PARSER_VALUES_EQ(***oom2, zom2);
    ASSERT_PARSER_VALUES_EQ(*oom3, zom3);
    ASSERT_PARSER_VALUES_EQ(**oom3, zom3);
    ASSERT_PARSER_VALUES_EQ(***oom3, zom3);
    ASSERT_PARSER_VALUES_EQ(*oom4, zom4);
    ASSERT_PARSER_VALUES_EQ(**oom4, zom4);
    ASSERT_PARSER_VALUES_EQ(***oom4, zom4);
}

TEST("zero_or_more operator", "*zero_or_more_parser")
{
    ASSERT_PARSER_VALUES_EQ(*zom1, zom1);
    ASSERT_PARSER_VALUES_EQ(**zom1, zom1);
    ASSERT_PARSER_VALUES_EQ(***zom1, zom1);
    ASSERT_PARSER_VALUES_EQ(*zom2, zom2);
    ASSERT_PARSER_VALUES_EQ(**zom2, zom2);
    ASSERT_PARSER_VALUES_EQ(***zom2, zom2);
    ASSERT_PARSER_VALUES_EQ(*zom3, zom3);
    ASSERT_PARSER_VALUES_EQ(**zom3, zom3);
    ASSERT_PARSER_VALUES_EQ(***zom3, zom3);
    ASSERT_PARSER_VALUES_EQ(*zom4, zom4);
    ASSERT_PARSER_VALUES_EQ(**zom4, zom4);
    ASSERT_PARSER_VALUES_EQ(***zom4, zom4);
}

TEST("zero_or_more operator", "non consteval")
{
    (*any1).parse(TT("abc"));
}



#define ZERO_OR_MORE_OPERATOR_ASSERTER(P)                                               \
    []<parser PP>(PP) {                                                                 \
        DEP_ASSERT_UNARY_OPERABLE(*, PP{}, P{});                                        \
        if constexpr (PP::family == maybe_family)                                       \
        {                                                                               \
            DEP_ASSERT_PARSER_VALUES_EQ(*PP{}, zero_or_more_parser<underlying_t<PP>>{}, \
                                        *P{},  zero_or_more_parser<underlying_t<P>>{}); \
        }                                                                               \
        else if constexpr (PP::family == one_or_more_family)                            \
        {                                                                               \
            DEP_ASSERT_PARSER_VALUES_EQ(*PP{}, zero_or_more_parser<underlying_t<PP>>{}, \
                                        *P{},  zero_or_more_parser<underlying_t<P>>{}); \
        }                                                                               \
        else if constexpr (PP::family == zero_or_more_family)                           \
        {                                                                               \
            DEP_ASSERT_PARSER_VALUES_EQ(*PP{}, PP{},                                    \
                                        *P{},  P{});                                    \
        }                                                                               \
        else                                                                            \
        {                                                                               \
            DEP_ASSERT_PARSER_VALUES_EQ(*PP{}, zero_or_more_parser<PP>{},               \
                                        *P{},  zero_or_more_parser<P>{});               \
        }                                                                               \
    }(P{});

TEST("zero_or_more operator", "*{anything}")
{
    ASSERT_ALL_SAMPLES(ZERO_OR_MORE_OPERATOR_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
