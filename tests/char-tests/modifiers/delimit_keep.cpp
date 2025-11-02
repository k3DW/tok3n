// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("delimit_keep modifier");

TEST("delimit_keep modifier", "prefix")
{
    EXPECT_THAT(parser_value<dek1>
                         .is<delimit_keep(abc, comma)>);
    EXPECT_THAT(parser_value<dek2>
                         .is<delimit_keep(abc, spacedot)>);
    EXPECT_THAT(parser_value<dek3>
                         .is<delimit_keep(qq, comma)>);
    EXPECT_THAT(parser_value<dek4>
                         .is<delimit_keep(qq, spacedot)>);
    EXPECT_THAT(parser_value<dek5>
                         .is<delimit_keep(comma, abc)>);
    EXPECT_THAT(parser_value<dek6>
                         .is<delimit_keep(spacedot, abc)>);
    EXPECT_THAT(parser_value<dek7>
                         .is<delimit_keep(comma, qq)>);
    EXPECT_THAT(parser_value<dek8>
                         .is<delimit_keep(spacedot, qq)>);
}

TEST("delimit_keep modifier", "infix")
{
    EXPECT_THAT(parser_value<dek1>
                         .is<abc % delimit_keep(comma)>);
    EXPECT_THAT(parser_value<dek2>
                         .is<abc % delimit_keep(spacedot)>);
    EXPECT_THAT(parser_value<dek3>
                         .is<qq % delimit_keep(comma)>);
    EXPECT_THAT(parser_value<dek4>
                         .is<qq % delimit_keep(spacedot)>);
    EXPECT_THAT(parser_value<dek5>
                         .is<comma % delimit_keep(abc)>);
    EXPECT_THAT(parser_value<dek6>
                         .is<spacedot % delimit_keep(abc)>);
    EXPECT_THAT(parser_value<dek7>
                         .is<comma % delimit_keep(qq)>);
    EXPECT_THAT(parser_value<dek8>
                         .is<spacedot % delimit_keep(qq)>);
}

TEST("delimit_keep modifier", "non consteval")
{
    (delimit_keep(any1, any2)).parse(TT("abc"));
    (any1 % delimit_keep(any2)).parse(TT("abc"));
}



#define DELIMIT_KEEP_MODIFIER_ASSERTER(P)                                                   \
    []<parser PP>(PP) {                                                                     \
        using R = delimit_parser<PP, Comma>;                                                \
        EXPECT_THAT(the_parser<PP> | is_modifiable_by<delimit_keep(comma)>.with_result<R>); \
    }(P{});

#define DELIMIT_KEEP_MODIFIER_ASSERTER_2(P, D)                                                 \
    []<parser PP, parser DD>(PP, DD) {                                                         \
        if constexpr (not std::same_as<typename PP::value_type, typename DD::value_type>)      \
        {                                                                                      \
            EXPECT_THAT(the_parser<PP> | is_not_modifiable_by<delimit_keep(DD{})>);            \
            ASSERT_COMPILE_TIME((not requires { delimit_keep(PP{}, DD{}); }));                 \
        }                                                                                      \
        else                                                                                   \
        {                                                                                      \
            using R = delimit_parser<PP, DD>;                                                  \
            EXPECT_THAT(the_parser<PP> | is_modifiable_by<delimit_keep(DD{})>.with_result<R>); \
            ASSERT_COMPILE_TIME((std::same_as<R, decltype(delimit_keep(PP{}, DD{}))>));        \
        }                                                                                      \
    }(P{}, D{});

#define DELIMIT_KEEP_SAMPLES_LIST_DIFFERENT_VALUE_TYPES \
    (any_of_parser<"abc">) (any_of_parser<"xyz">) (any_of_parser<L"abc">) (any_of_parser<L"xyz">)

TEST("delimit_keep modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(DELIMIT_KEEP_MODIFIER_ASSERTER);

    ASSERT_SAMPLES_2(
        DELIMIT_KEEP_MODIFIER_ASSERTER_2,
        DELIMIT_KEEP_SAMPLES_LIST_DIFFERENT_VALUE_TYPES,
        DELIMIT_KEEP_SAMPLES_LIST_DIFFERENT_VALUE_TYPES
    );
}

} // namespace
} // namespace k3::tok3n::tests
