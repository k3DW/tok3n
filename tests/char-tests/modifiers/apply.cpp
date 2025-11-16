// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("apply modifier");

TEST("apply modifier", "prefix")
{
    EXPECT_THAT(parser_value<apm1>
                         .is<apply<func3_apply>(abc >> *qq)>);
    EXPECT_THAT(parser_value<apm2>
                         .is<apply<func4_apply(3)>(+abc >> ~(abc | qq))>);
    EXPECT_THAT(parser_value<apm2>
                     .is_not<apply<func4_apply(2)>(+abc >> ~(abc | qq))>);
}

TEST("apply modifier", "infix")
{
    EXPECT_THAT(parser_value<apm1>
                         .is<(abc >> *qq) % apply<func3_apply>>);
    EXPECT_THAT(parser_value<apm2>
                         .is<(+abc >> ~(abc | qq)) % apply<func4_apply(3)>>);
    EXPECT_THAT(parser_value<apm2>
                     .is_not<(+abc >> ~(abc | qq)) % apply<func4_apply(2)>>);
}

TEST("apply modifier", "non consteval")
{
    (apply<sink_func>(any1 >> any2)).parse(TT("abc"));
    ((any1 >> any2) % apply<sink_func>).parse(TT("abc"));
}



#define APPLY_MODIFIER_ASSERTER(P)                                                          \
    []<parser PP>(PP) {                                                                     \
        constexpr auto m = apply<sink_func>;                                                \
        using R = apply_map_parser<PP, integral_constant<sink_func>>;                       \
        EXPECT_THAT(the_parser<PP> | is_modifiable_by<m>.TEMPLATE_IF_GCC12 with_result<R>); \
    }(P{});

TEST("apply modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(APPLY_MODIFIER_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
