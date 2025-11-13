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



constexpr auto delimit_keep_modifier_fragment =
    []<detail::parser P>(P) {
        using R = delimit_parser<P, Comma>;
        EXPECT_THAT(the_parser<P> | is_modifiable_by<delimit_keep(comma)>.TEMPLATE_IF_GCC12 with_result<R>);
    };

constexpr auto delimit_keep_modifier_pairs_fragment =
    []<detail::parser P, detail::parser D>(P, D) {
        if constexpr (not std::same_as<typename P::value_type, typename D::value_type>)
        {
            EXPECT_THAT(the_parser<P> | is_not_modifiable_by<delimit_keep(D{})>);
            ASSERT_COMPILE_TIME((not requires { delimit_keep(P{}, D{}); }));
        }
        else
        {
            using R = delimit_parser<P, D>;
            EXPECT_THAT(the_parser<P> | is_modifiable_by<delimit_keep(D{})>.DEP_TEMPLATE with_result<R>);
            ASSERT_COMPILE_TIME((std::same_as<R, decltype(delimit_keep(P{}, D{}))>));
        }
    };

TEST("delimit_keep modifier", "modify anything")
{
    EXPECT_THAT(all_samples.satisfy(delimit_keep_modifier_fragment));

    using Samples = parser_list_t<
        any_of_parser<"abc">,
        any_of_parser<"xyz">,
        any_of_parser<L"abc">,
        any_of_parser<L"xyz">
    >;
    EXPECT_THAT((pairs_of_samples<Samples, Samples>.satisfy(delimit_keep_modifier_pairs_fragment)));
}

} // namespace
} // namespace k3::tok3n::tests
