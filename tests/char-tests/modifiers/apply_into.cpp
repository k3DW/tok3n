// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("apply_into modifier");

TEST("apply_into modifier", "prefix")
{
    ASSERT_PARSER_VALUES_EQ(api1, apply_into<Class2>(abc >> spacedot));
    ASSERT_PARSER_VALUES_EQ(api2, apply_into<Class5>(spacedot >> abc));
}

TEST("apply_into modifier", "infix")
{
    ASSERT_PARSER_VALUES_EQ(api1, (abc >> spacedot) % apply_into<Class2>);
    ASSERT_PARSER_VALUES_EQ(api2, (spacedot >> abc) % apply_into<Class5>);
}

TEST("apply_into modifier", "non consteval")
{
    (apply_into<Sink>(any1 >> any2)).parse(TT("abc"));
    ((any1 >> any2) % apply_into<Sink>).parse(TT("abc"));
}



#define APPLY_INTO_MODIFIER_ASSERTER(P)                                                                \
    []<parser PP>(PP) {                                                                                \
        DEP_ASSERT_MODIFIER_CALLABLE_R(apply_into<Sink>, (PP{}), (apply_into_parser<PP, Sink>{}),      \
                                       apply_into<Sink>, (P{}),  (apply_into_parser<P, Sink>{}));      \
        DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, apply_into<Sink>, (apply_into_parser<PP, Sink>{}), \
                                              P{},  apply_into<Sink>, (apply_into_parser<P, Sink>{})); \
    }(P{});

TEST("apply_into modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(APPLY_INTO_MODIFIER_ASSERTER);
}
