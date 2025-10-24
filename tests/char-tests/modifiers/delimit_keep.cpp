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



#define DELIMIT_KEEP_MODIFIER_ASSERTER(P)                                                               \
    []<parser PP>(PP) {                                                                                 \
        DEP_ASSERT_MODIFIER_CALLABLE_R(delimit_keep, (PP{}, comma), (delimit_parser<PP, Comma>{}),      \
                                       delimit_keep, (P{}, comma),  (delimit_parser<P, Comma>{}));      \
        DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, delimit_keep(comma), (delimit_parser<PP, Comma>{}), \
                                              P{},  delimit_keep(comma), (delimit_parser<P, Comma>{})); \
    }(P{});

#define DELIMIT_KEEP_MODIFIER_ASSERTER_2(P, D)                                                          \
    []<parser PP, parser DD>(PP, DD) {                                                                  \
        if constexpr (not std::same_as<typename PP::value_type, typename DD::value_type>)               \
        {                                                                                               \
            DEP_ASSERT_MODIFIER_NOT_CALLABLE(delimit_keep, (PP{}, DD{}),                                \
                                             delimit_keep, (P{},  D{}));                                \
            DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(PP{}, delimit_keep(DD{}),                           \
                                                    P{},  delimit_keep(D{}));                           \
        }                                                                                               \
        else                                                                                            \
        {                                                                                               \
            DEP_ASSERT_MODIFIER_CALLABLE_R(delimit_keep, (PP{}, DD{}), (delimit_parser<PP, DD>{}),      \
                                           delimit_keep, (P{},  D{}),  (delimit_parser<P, D>{}));       \
            DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, delimit_keep(DD{}), (delimit_parser<PP, DD>{}), \
                                                  P{},  delimit_keep(D{}),  (delimit_parser<P, D>{}));  \
        }                                                                                               \
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
