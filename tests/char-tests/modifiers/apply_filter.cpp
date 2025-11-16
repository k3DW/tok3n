// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("apply_filter modifier");

TEST("apply_filter modifier", "prefix")
{
    EXPECT_THAT(parser_value<apf1>
                         .is<apply_filter<filter_func3_apply>(abc >> *qq)>);
}

TEST("apply_filter modifier", "infix")
{
    EXPECT_THAT(parser_value<apf1>
                         .is<(abc >> *qq) % apply_filter<filter_func3_apply>>);
}

TEST("apply_filter modifier", "non consteval")
{
    (apply_filter<true_filter>(any1 >> any2)).parse(TT("abc"));
    ((any1 >> any2) % apply_filter<true_filter>).parse(TT("abc"));
}



#define APPLY_FILTER_MODIFIER_ASSERTER(P)                                                   \
    []<parser PP>(PP) {                                                                     \
        constexpr auto m = apply_filter<true_filter>;                                       \
        using R = apply_filter_parser<PP, integral_constant<true_filter>>;                  \
        EXPECT_THAT(the_parser<PP> | is_modifiable_by<m>.TEMPLATE_IF_GCC12 with_result<R>); \
    }(P{});

TEST("apply_filter modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(APPLY_FILTER_MODIFIER_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
