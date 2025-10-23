// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("delimit modifier");

TEST("delimit modifier", "prefix")
{
    ASSERT_PARSER_VALUES_EQ(del1, delimit(abc, comma));
    ASSERT_PARSER_VALUES_EQ(del2, delimit(abc, spacedot));
    ASSERT_PARSER_VALUES_EQ(del3, delimit(qq, comma));
    ASSERT_PARSER_VALUES_EQ(del4, delimit(qq, spacedot));
    ASSERT_PARSER_VALUES_EQ(del5, delimit(comma, abc));
    ASSERT_PARSER_VALUES_EQ(del6, delimit(spacedot, abc));
    ASSERT_PARSER_VALUES_EQ(del7, delimit(comma, qq));
    ASSERT_PARSER_VALUES_EQ(del8, delimit(spacedot, qq));
}

TEST("delimit modifier", "infix")
{
    ASSERT_PARSER_VALUES_EQ(del1, abc % delimit(comma));
    ASSERT_PARSER_VALUES_EQ(del2, abc % delimit(spacedot));
    ASSERT_PARSER_VALUES_EQ(del3, qq % delimit(comma));
    ASSERT_PARSER_VALUES_EQ(del4, qq % delimit(spacedot));
    ASSERT_PARSER_VALUES_EQ(del5, comma % delimit(abc));
    ASSERT_PARSER_VALUES_EQ(del6, spacedot % delimit(abc));
    ASSERT_PARSER_VALUES_EQ(del7, comma % delimit(qq));
    ASSERT_PARSER_VALUES_EQ(del8, spacedot % delimit(qq));
}

TEST("delimit modifier", "non consteval")
{
    (delimit(any1, any2)).parse(TT("abc"));
    (any1 % delimit(any2)).parse(TT("abc"));
}



#define DELIMIT_MODIFIER_ASSERTER(P)                                                                              \
    []<parser PP>(PP) {                                                                                           \
        DEP_ASSERT_MODIFIER_CALLABLE_R(delimit, (PP{}, comma), (delimit_parser<PP, ignore_parser<Comma>>{}),      \
                                       delimit, (P{}, comma),  (delimit_parser<P, ignore_parser<Comma>>{}));      \
        DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, delimit(comma), (delimit_parser<PP, ignore_parser<Comma>>{}), \
                                              P{},  delimit(comma), (delimit_parser<P, ignore_parser<Comma>>{})); \
    }(P{});

#define DELIMIT_MODIFIER_ASSERTER_2(P, D)                                                                         \
    []<parser PP, parser DD>(PP, DD) {                                                                            \
        if constexpr (not std::same_as<typename PP::value_type, typename DD::value_type>)                         \
        {                                                                                                         \
            DEP_ASSERT_MODIFIER_NOT_CALLABLE(delimit, (PP{}, DD{}),                                               \
                                             delimit, (P{},  D{}));                                               \
            DEP_ASSERT_MODIFIER_NOT_MODULO_OPERABLE(PP{}, delimit(DD{}),                                          \
                                                    P{},  delimit(D{}));                                          \
        }                                                                                                         \
        else                                                                                                      \
        {                                                                                                         \
            DEP_ASSERT_MODIFIER_CALLABLE_R(delimit, (PP{}, DD{}), (delimit_parser<PP, ignore_parser<DD>>{}),      \
                                           delimit, (P{},  D{}),  (delimit_parser<P, ignore_parser<D>>{}));       \
            DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, delimit(DD{}), (delimit_parser<PP, ignore_parser<DD>>{}), \
                                                  P{},  delimit(D{}),  (delimit_parser<P, ignore_parser<D>>{}));  \
        }                                                                                                         \
    }(P{}, D{});

#define DELIMIT_SAMPLES_LIST_DIFFERENT_VALUE_TYPES \
    (any_of_parser<"abc">) (any_of_parser<"xyz">) (any_of_parser<L"abc">) (any_of_parser<L"xyz">)

TEST("delimit modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(DELIMIT_MODIFIER_ASSERTER);

    ASSERT_SAMPLES_2(
        DELIMIT_MODIFIER_ASSERTER_2,
        DELIMIT_SAMPLES_LIST_DIFFERENT_VALUE_TYPES,
        DELIMIT_SAMPLES_LIST_DIFFERENT_VALUE_TYPES
    );
}

} // namespace
} // namespace k3::tok3n::tests
