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



constexpr auto apply_filter_modifier_fragment =
    []<detail::parser P>(P) {
        constexpr auto m = apply_filter<true_filter>;
        using R = apply_filter_parser<P, integral_constant<true_filter>>;
        EXPECT_THAT(the_parser<P> | is_modifiable_by<m>.TEMPLATE_IF_GCC12 with_result<R>);
    };

TEST("apply_filter modifier", "modify anything")
{
    EXPECT_THAT(all_samples.satisfy(apply_filter_modifier_fragment));
}

} // namespace
} // namespace k3::tok3n::tests
