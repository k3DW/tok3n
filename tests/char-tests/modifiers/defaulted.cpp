// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

using namespace k3::tok3n;
using namespace k3::tok3n::detail;

FIXTURE("defaulted modifier");

TEST("defaulted modifier", "prefix")
{
    ASSERT_PARSER_VALUES_EQ(def1, defaulted<int>(+abc));
    ASSERT_PARSER_VALUES_EQ(def2, defaulted<Class3>(~(abc | qq)));
}

TEST("defaulted modifier", "infix")
{
    ASSERT_PARSER_VALUES_EQ(def1, +abc % defaulted<int>);
    ASSERT_PARSER_VALUES_EQ(def2, ~(abc | qq) % defaulted<Class3>);
}

TEST("defaulted modifier", "non consteval")
{
    (defaulted<int>(any1)).parse(TT("abc"));
    (any1 % defaulted<int>).parse(TT("abc"));
}



#define DEFAULTED_MODIFIER_ASSERTER(P)                                                      \
    ASSERT_MODIFIER_CALLABLE_R(defaulted<bool>, (P{}), (defaulted_parser<P, bool>{}));      \
    ASSERT_MODIFIER_MODULO_OPERABLE_R(P{}, defaulted<bool>, (defaulted_parser<P, bool>{}));

TEST("defaulted modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(DEFAULTED_MODIFIER_ASSERTER);
}
