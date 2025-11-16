// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("apply_into modifier");

TEST("apply_into modifier", "prefix")
{
    EXPECT_THAT(parser_value<api1>
                         .is<apply_into<Class2>(abc >> spacedot)>);
    EXPECT_THAT(parser_value<api2>
                         .is<apply_into<Class5>(spacedot >> abc)>);
}

TEST("apply_into modifier", "infix")
{
    EXPECT_THAT(parser_value<api1>
                         .is<(abc >> spacedot) % apply_into<Class2>>);
    EXPECT_THAT(parser_value<api2>
                         .is<(spacedot >> abc) % apply_into<Class5>>);
}

TEST("apply_into modifier", "non consteval")
{
    (apply_into<Sink>(any1 >> any2)).parse(TT("abc"));
    ((any1 >> any2) % apply_into<Sink>).parse(TT("abc"));
}



#define APPLY_INTO_MODIFIER_ASSERTER(P)                                                     \
    []<parser PP>(PP) {                                                                     \
        constexpr auto m = apply_into<Sink>;                                                \
        using R = apply_into_parser<PP, Sink>;                                              \
        EXPECT_THAT(the_parser<PP> | is_modifiable_by<m>.TEMPLATE_IF_GCC12 with_result<R>); \
    }(P{});

TEST("apply_into modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(APPLY_INTO_MODIFIER_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
