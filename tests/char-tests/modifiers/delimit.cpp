// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("delimit modifier");

TEST("delimit modifier", "prefix")
{
    EXPECT_THAT(parser_value<del1>
                         .is<delimit(abc, comma)>);
    EXPECT_THAT(parser_value<del2>
                         .is<delimit(abc, spacedot)>);
    EXPECT_THAT(parser_value<del3>
                         .is<delimit(qq, comma)>);
    EXPECT_THAT(parser_value<del4>
                         .is<delimit(qq, spacedot)>);
    EXPECT_THAT(parser_value<del5>
                         .is<delimit(comma, abc)>);
    EXPECT_THAT(parser_value<del6>
                         .is<delimit(spacedot, abc)>);
    EXPECT_THAT(parser_value<del7>
                         .is<delimit(comma, qq)>);
    EXPECT_THAT(parser_value<del8>
                         .is<delimit(spacedot, qq)>);
}

TEST("delimit modifier", "infix")
{
    EXPECT_THAT(parser_value<del1>
                         .is<abc % delimit(comma)>);
    EXPECT_THAT(parser_value<del2>
                         .is<abc % delimit(spacedot)>);
    EXPECT_THAT(parser_value<del3>
                         .is<qq % delimit(comma)>);
    EXPECT_THAT(parser_value<del4>
                         .is<qq % delimit(spacedot)>);
    EXPECT_THAT(parser_value<del5>
                         .is<comma % delimit(abc)>);
    EXPECT_THAT(parser_value<del6>
                         .is<spacedot % delimit(abc)>);
    EXPECT_THAT(parser_value<del7>
                         .is<comma % delimit(qq)>);
    EXPECT_THAT(parser_value<del8>
                         .is<spacedot % delimit(qq)>);
}

TEST("delimit modifier", "non consteval")
{
    (delimit(any1, any2)).parse(TT("abc"));
    (any1 % delimit(any2)).parse(TT("abc"));
}



constexpr auto delimit_modifier_fragment =
    []<detail::parser P>(P) {
        using R = delimit_parser<P, ignore_parser<Comma>>;
        EXPECT_THAT(the_parser<P> | is_modifiable_by<delimit(comma)>.TEMPLATE_IF_GCC12 with_result<R>);
    };

#define DELIMIT_MODIFIER_ASSERTER_2(P, D)                                                              \
    []<parser PP, parser DD>(PP, DD) {                                                                 \
        if constexpr (not std::same_as<typename PP::value_type, typename DD::value_type>)              \
        {                                                                                              \
            EXPECT_THAT(the_parser<PP> | is_not_modifiable_by<delimit(DD{})>);                         \
            ASSERT_COMPILE_TIME((not requires { delimit(PP{}, DD{}); }));                              \
        }                                                                                              \
        else                                                                                           \
        {                                                                                              \
            using R = delimit_parser<PP, ignore_parser<DD>>;                                           \
            EXPECT_THAT(the_parser<PP> | is_modifiable_by<delimit(DD{})>.DEP_TEMPLATE with_result<R>); \
            ASSERT_COMPILE_TIME((std::same_as<R, decltype(delimit(PP{}, DD{}))>));                     \
        }                                                                                              \
    }(P{}, D{});

#define DELIMIT_SAMPLES_LIST_DIFFERENT_VALUE_TYPES \
    (any_of_parser<"abc">) (any_of_parser<"xyz">) (any_of_parser<L"abc">) (any_of_parser<L"xyz">)

TEST("delimit modifier", "modify anything")
{
    EXPECT_THAT(all_samples.satisfy(delimit_modifier_fragment));

    ASSERT_SAMPLES_2(
        DELIMIT_MODIFIER_ASSERTER_2,
        DELIMIT_SAMPLES_LIST_DIFFERENT_VALUE_TYPES,
        DELIMIT_SAMPLES_LIST_DIFFERENT_VALUE_TYPES
    );
}

} // namespace
} // namespace k3::tok3n::tests
