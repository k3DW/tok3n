// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("sub modifier");

namespace {

constexpr auto sub11 = (name<"nam1"> = ignore);
constexpr auto sub21 = (name<"nam2"> = join);
constexpr auto sub31 = (name<"nam3"> = name<"nam2">);
constexpr auto sub41 = (name<"nam4"> = exactly<2>);
constexpr auto sub12 = (name<"nam1"> = join);
constexpr auto sub22 = (name<"nam2"> = ignore);
constexpr auto sub32 = (name<"nam3"> = exactly<2>);
constexpr auto sub42 = (name<"nam4"> = name<"nam2">);

} // namespace

#define ASSERT_SUBSTITUTION_TYPE(SUB, NAME, SUBBED)                                                                            \
    ASSERT(substitution<decltype(SUB)>) << #SUB " is expected to satisfy substitution concept.";                               \
    ASSERT(std::is_empty_v<decltype(SUB)>) << #SUB " is expected to be an empty type.";                                        \
    ASSERT((std::same_as<std::remove_cvref_t<decltype(SUB)>, substitution_info<NAME, std::remove_cvref_t<decltype(SUBBED)>>>)) \
        << #SUB " must be the same as substitution_info<" NAME ", decltype(" #SUBBED ")>."

#define ASSERT_SUBSTITUTION_SAME_NAME(SUB1, SUB2)                                      \
    ASSERT((not std::same_as<decltype(SUB1), decltype(SUB2)>))                         \
        << #SUB1 " and " #SUB2 " must not be the same type.";                          \
    ASSERT(SUB1.name == SUB2.name) << #SUB1 " and " #SUB2 " must have the same name."; \
    ASSERT((not std::same_as<decltype(SUB1.mod), decltype(SUB2.mod)>))                 \
        << #SUB1 " and " #SUB2 " must not have the same substituted modifier."

TEST("sub modifier", "create substitutions")
{
    ASSERT_SUBSTITUTION_TYPE(sub11, "nam1", ignore);
    ASSERT_SUBSTITUTION_TYPE(sub21, "nam2", join);
    ASSERT_SUBSTITUTION_TYPE(sub31, "nam3", name<"nam2">);
    ASSERT_SUBSTITUTION_TYPE(sub41, "nam4", exactly<2>);
    ASSERT_SUBSTITUTION_TYPE(sub12, "nam1", join);
    ASSERT_SUBSTITUTION_TYPE(sub22, "nam2", ignore);
    ASSERT_SUBSTITUTION_TYPE(sub32, "nam3", exactly<2>);
    ASSERT_SUBSTITUTION_TYPE(sub42, "nam4", name<"nam2">);

    ASSERT_SUBSTITUTION_SAME_NAME(sub11, sub12);
    ASSERT_SUBSTITUTION_SAME_NAME(sub21, sub22);
    ASSERT_SUBSTITUTION_SAME_NAME(sub31, sub32);
    ASSERT_SUBSTITUTION_SAME_NAME(sub41, sub42);
}

TEST("sub modifier", "prefix")
{
    EXPECT_THAT(parser_value<sub(nam1, sub11)>
                         .is<ignore_parser<_21>{}>);
    EXPECT_THAT(parser_value<sub(nam1, sub21)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<sub(nam1, sub31)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<sub(nam1, sub41)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<sub(nam1, sub12)>
                         .is<join_parser<_21>{}>);
    EXPECT_THAT(parser_value<sub(nam1, sub22)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<sub(nam1, sub32)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<sub(nam1, sub42)>
                         .is<nam1>);

    EXPECT_THAT(parser_value<sub(nam2, sub11)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<sub(nam2, sub21)>
                         .is<join_parser<_22>{}>);
    EXPECT_THAT(parser_value<sub(nam2, sub31)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<sub(nam2, sub41)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<sub(nam2, sub12)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<sub(nam2, sub22)>
                         .is<ignore_parser<_22>{}>);
    EXPECT_THAT(parser_value<sub(nam2, sub32)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<sub(nam2, sub42)>
                         .is<nam2>);

    EXPECT_THAT(parser_value<sub(nam3, sub11)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<sub(nam3, sub21)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<sub(nam3, sub31)>
                         .is<(named_parser<_23, "nam2">{})>);
    EXPECT_THAT(parser_value<sub(nam3, sub41)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<sub(nam3, sub12)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<sub(nam3, sub32)>
                         .is<(exactly_parser<_23, index_c<2>>{})>);
    EXPECT_THAT(parser_value<sub(nam3, sub32)>
                         .is<(exactly_parser<_23, index_c<2>>{})>);
    EXPECT_THAT(parser_value<sub(nam3, sub42)>
                         .is<nam3>);

    EXPECT_THAT(parser_value<sub(nam4, sub11)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<sub(nam4, sub21)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<sub(nam4, sub31)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<sub(nam4, sub41)>
                         .is<(exactly_parser<_24, index_c<2>>{})>);
    EXPECT_THAT(parser_value<sub(nam4, sub12)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<sub(nam4, sub22)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<sub(nam4, sub32)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<sub(nam4, sub42)>
                         .is<(named_parser<_24, "nam2">{})>);
}

TEST("sub modifier", "infix")
{
    EXPECT_THAT(parser_value<nam1 % sub(sub11)>
                         .is<ignore_parser<_21>{}>);
    EXPECT_THAT(parser_value<nam1 % sub(sub21)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<nam1 % sub(sub31)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<nam1 % sub(sub41)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<nam1 % sub(sub12)>
                         .is<join_parser<_21>{}>);
    EXPECT_THAT(parser_value<nam1 % sub(sub22)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<nam1 % sub(sub32)>
                         .is<nam1>);
    EXPECT_THAT(parser_value<nam1 % sub(sub42)>
                         .is<nam1>);

    EXPECT_THAT(parser_value<nam2 % sub(sub11)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<nam2 % sub(sub21)>
                         .is<join_parser<_22>{}>);
    EXPECT_THAT(parser_value<nam2 % sub(sub31)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<nam2 % sub(sub41)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<nam2 % sub(sub12)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<nam2 % sub(sub22)>
                         .is<ignore_parser<_22>{}>);
    EXPECT_THAT(parser_value<nam2 % sub(sub32)>
                         .is<nam2>);
    EXPECT_THAT(parser_value<nam2 % sub(sub42)>
                         .is<nam2>);

    EXPECT_THAT(parser_value<nam3 % sub(sub11)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<nam3 % sub(sub21)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<nam3 % sub(sub31)>
                         .is<(named_parser<_23, "nam2">{})>);
    EXPECT_THAT(parser_value<nam3 % sub(sub41)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<nam3 % sub(sub12)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<nam3 % sub(sub22)>
                         .is<nam3>);
    EXPECT_THAT(parser_value<nam3 % sub(sub32)>
                         .is<(exactly_parser<_23, index_c<2>>{})>);
    EXPECT_THAT(parser_value<nam3 % sub(sub42)>
                         .is<nam3>);

    EXPECT_THAT(parser_value<nam4 % sub(sub11)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<nam4 % sub(sub21)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<nam4 % sub(sub31)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<nam4 % sub(sub41)>
                         .is<(exactly_parser<_24, index_c<2>>{})>);
    EXPECT_THAT(parser_value<nam4 % sub(sub12)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<nam4 % sub(sub22)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<nam4 % sub(sub32)>
                         .is<nam4>);
    EXPECT_THAT(parser_value<nam4 % sub(sub42)>
                         .is<(named_parser<_24, "nam2">{})>);
}

TEST("sub modifier", "order-dependent")
{
    EXPECT_THAT(parser_value<nam3 % sub(sub21, sub31)>
                         .is<(named_parser<_23, "nam2">{})>);
    EXPECT_THAT(parser_value<nam3 % sub(sub31, sub21)>
                         .is<join_parser<_23>{}>);
}

TEST("sub modifier", "chainable")
{
    EXPECT_THAT(parser_value<nam3 % sub(sub21, sub31)>
                         .is<nam3 % sub(sub21) % sub(sub31)>);
    EXPECT_THAT(parser_value<nam3 % sub(sub31, sub21)>
                         .is<nam3 % sub(sub31) % sub(sub21)>);
}

TEST("sub modifier", "non consteval")
{
    (sub(nam1, sub11)).parse(TT("abc"));
    (nam1 % sub(sub11)).parse(TT("abc"));
}

} // namespace
} // namespace k3::tok3n::tests
