// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("apply modifier");

TEST("apply modifier", "prefix")
{
    ASSERT_PARSER_VALUES_EQ(apm1, apply<func3_apply>(abc >> *qq));
    ASSERT_PARSER_VALUES_EQ(apm2, apply<func4_apply(3)>(+abc >> ~(abc | qq)));
    ASSERT_PARSER_VALUES_NE(apm2, apply<func4_apply(2)>(+abc >> ~(abc | qq)));
}

TEST("apply modifier", "infix")
{
    ASSERT_PARSER_VALUES_EQ(apm1, (abc >> *qq) % apply<func3_apply>);
    ASSERT_PARSER_VALUES_EQ(apm2, (+abc >> ~(abc | qq)) % apply<func4_apply(3)>);
    ASSERT_PARSER_VALUES_NE(apm2, (+abc >> ~(abc | qq)) % apply<func4_apply(2)>);
}

TEST("apply modifier", "non consteval")
{
    (apply<sink_func>(any1 >> any2)).parse(TT("abc"));
    ((any1 >> any2) % apply<sink_func>).parse(TT("abc"));
}



#define APPLY_MODIFIER_ASSERTER(P)                                                                                            \
    []<parser PP>(PP) {                                                                                                       \
        DEP_ASSERT_MODIFIER_CALLABLE_R(apply<sink_func>, (PP{}), (apply_map_parser<PP, integral_constant<sink_func>>{}),      \
                                       apply<sink_func>, (P{}),  (apply_map_parser<P, integral_constant<sink_func>>{}));      \
        DEP_ASSERT_MODIFIER_MODULO_OPERABLE_R(PP{}, apply<sink_func>, (apply_map_parser<PP, integral_constant<sink_func>>{}), \
                                              P{},  apply<sink_func>, (apply_map_parser<P, integral_constant<sink_func>>{})); \
    }(P{});

TEST("apply modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(APPLY_MODIFIER_ASSERTER);
}
