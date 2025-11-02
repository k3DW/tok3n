// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("filter modifier");

TEST("filter modifier", "prefix")
{
    EXPECT_THAT(parser_value<fil1>
                         .is<filter<filter_func1>(+abc)>);
    EXPECT_THAT(parser_value<fil2>
                         .is<filter<filter_func2>(~(abc | qq))>);
    EXPECT_THAT(parser_value<fil3>
                         .is<filter<filter_func3>(abc >> *qq)>);
}

TEST("filter modifier", "infix")
{
    EXPECT_THAT(parser_value<fil1>
                         .is<+abc % filter<filter_func1>>);
    EXPECT_THAT(parser_value<fil2>
                         .is<~(abc | qq) % filter<filter_func2>>);
    EXPECT_THAT(parser_value<fil3>
                         .is<(abc >> *qq) % filter<filter_func3>>);
}

TEST("filter modifier", "non consteval")
{
    (filter<true_filter>(any1)).parse(TT("abc"));
    (any1 % filter<true_filter>).parse(TT("abc"));
}



#define FILTER_MODIFIER_ASSERTER(P)                                       \
    []<parser PP>(PP) {                                                   \
        constexpr auto m = filter<true_filter>;                           \
        using R = filter_parser<PP, integral_constant<true_filter>>;      \
        EXPECT_THAT(the_parser<PP> | is_modifiable_by<m>.with_result<R>); \
    }(P{});

TEST("filter modifier", "modify anything")
{
    ASSERT_ALL_SAMPLES(FILTER_MODIFIER_ASSERTER);
}

} // namespace
} // namespace k3::tok3n::tests
