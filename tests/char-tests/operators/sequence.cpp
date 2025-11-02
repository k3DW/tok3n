// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include "samples.hpp"

namespace k3::tok3n::tests {
namespace {

FIXTURE("sequence operator");

TEST("sequence operator", "all_of_parser >> all_of_parser")
{
    EXPECT_THAT(parser_value<(all1 >> all1)>
                         .is<all_of_parser<TT("literalliteral")>{}>);
    EXPECT_THAT(parser_value<(all1 >> all2)>
                         .is<all_of_parser<TT("literally")>{}>);
    EXPECT_THAT(parser_value<(all1 >> all3)>
                         .is<all_of_parser<TT("literaltest")>{}>);
    EXPECT_THAT(parser_value<(all2 >> all1)>
                         .is<all_of_parser<TT("lyliteral")>{}>);
    EXPECT_THAT(parser_value<(all2 >> all2)>
                         .is<all_of_parser<TT("lyly")>{}>);
    EXPECT_THAT(parser_value<(all2 >> all3)>
                         .is<all_of_parser<TT("lytest")>{}>);
    EXPECT_THAT(parser_value<(all3 >> all1)>
                         .is<all_of_parser<TT("testliteral")>{}>);
    EXPECT_THAT(parser_value<(all3 >> all2)>
                         .is<all_of_parser<TT("testly")>{}>);
    EXPECT_THAT(parser_value<(all3 >> all3)>
                         .is<all_of_parser<TT("testtest")>{}>);
}



TEST("sequence operator", "sequence_parser >> sequence_parser")
{
    EXPECT_THAT(parser_value<(seq1 >> seq1)>
                         .is<(sequence_parser<All4, Non4, All4, Non4>{})>);
    EXPECT_THAT(parser_value<(seq2 >> seq2)>
                         .is<(sequence_parser<Non4, All4, Non4, All4>{})>);
    EXPECT_THAT(parser_value<(seq3 >> seq3)>
                         .is<(sequence_parser<All4, Any4, Non5, All4, Any4, Non5>{})>);
    EXPECT_THAT(parser_value<(seq4 >> seq4)>
                         .is<(sequence_parser<Non5, All4, Any4, Non5, All4, Any4>{})>);
    EXPECT_THAT(parser_value<(seq5 >> seq5)>
                         .is<(sequence_parser<Ign1, Ign2, Ign1, Ign2>{})>);
    EXPECT_THAT(parser_value<(seq1 >> seq2)>
                         .is<(sequence_parser<All4, Non4, Non4, All4>{})>);
    EXPECT_THAT(parser_value<(seq2 >> seq1)>
                         .is<(sequence_parser<Non4, All4, All4, Non4>{})>);
    EXPECT_THAT(parser_value<(seq1 >> seq3)>
                         .is<(sequence_parser<All4, Non4, All4, Any4, Non5>{})>);
    EXPECT_THAT(parser_value<(seq3 >> seq1)>
                         .is<(sequence_parser<All4, Any4, Non5, All4, Non4>{})>);
    EXPECT_THAT(parser_value<(seq1 >> seq4)>
                         .is<(sequence_parser<All4, Non4, Non5, All4, Any4>{})>);
    EXPECT_THAT(parser_value<(seq4 >> seq1)>
                         .is<(sequence_parser<Non5, All4, Any4, All4, Non4>{})>);
    EXPECT_THAT(parser_value<(seq1 >> seq5)>
                         .is<(sequence_parser<All4, Non4, Ign1, Ign2>{})>);
    EXPECT_THAT(parser_value<(seq5 >> seq1)>
                         .is<(sequence_parser<Ign1, Ign2, All4, Non4>{})>);
    EXPECT_THAT(parser_value<(seq2 >> seq3)>
                         .is<(sequence_parser<Non4, All4, All4, Any4, Non5>{})>);
    EXPECT_THAT(parser_value<(seq3 >> seq2)>
                         .is<(sequence_parser<All4, Any4, Non5, Non4, All4>{})>);
    EXPECT_THAT(parser_value<(seq2 >> seq4)>
                         .is<(sequence_parser<Non4, All4, Non5, All4, Any4>{})>);
    EXPECT_THAT(parser_value<(seq4 >> seq2)>
                         .is<(sequence_parser<Non5, All4, Any4, Non4, All4>{})>);
    EXPECT_THAT(parser_value<(seq2 >> seq5)>
                         .is<(sequence_parser<Non4, All4, Ign1, Ign2>{})>);
    EXPECT_THAT(parser_value<(seq5 >> seq2)>
                         .is<(sequence_parser<Ign1, Ign2, Non4, All4>{})>);
    EXPECT_THAT(parser_value<(seq3 >> seq4)>
                         .is<(sequence_parser<All4, Any4, Non5, Non5, All4, Any4>{})>);
    EXPECT_THAT(parser_value<(seq4 >> seq3)>
                         .is<(sequence_parser<Non5, All4, Any4, All4, Any4, Non5>{})>);
    EXPECT_THAT(parser_value<(seq3 >> seq5)>
                         .is<(sequence_parser<All4, Any4, Non5, Ign1, Ign2>{})>);
    EXPECT_THAT(parser_value<(seq5 >> seq3)>
                         .is<(sequence_parser<Ign1, Ign2, All4, Any4, Non5>{})>);
    EXPECT_THAT(parser_value<(seq4 >> seq5)>
                         .is<(sequence_parser<Non5, All4, Any4, Ign1, Ign2>{})>);
    EXPECT_THAT(parser_value<(seq5 >> seq4)>
                         .is<(sequence_parser<Ign1, Ign2, Non5, All4, Any4>{})>);
}

TEST("sequence operator", "sequence_parser >> {anything}")
{
    EXPECT_THAT(parser_value<(seq1 >> any1)>
                         .is<(sequence_parser<All4, Non4, Any1>{})>);
    EXPECT_THAT(parser_value<(any1 >> seq1)>
                         .is<(sequence_parser<Any1, All4, Non4>{})>);
    EXPECT_THAT(parser_value<(seq2 >> any4)>
                         .is<(sequence_parser<Non4, All4, Any4>{})>);
    EXPECT_THAT(parser_value<(any4 >> seq2)>
                         .is<(sequence_parser<Any4, Non4, All4>{})>);
    EXPECT_THAT(parser_value<(seq3 >> any3)>
                         .is<(sequence_parser<All4, Any4, Non5, Any3>{})>);
    EXPECT_THAT(parser_value<(any3 >> seq3)>
                         .is<(sequence_parser<Any3, All4, Any4, Non5>{})>);
    EXPECT_THAT(parser_value<(seq4 >> any2)>
                         .is<(sequence_parser<Non5, All4, Any4, Any2>{})>);
    EXPECT_THAT(parser_value<(any2 >> seq4)>
                         .is<(sequence_parser<Any2, Non5, All4, Any4>{})>);
}

TEST("sequence operator", "void result_type")
{
    EXPECT_THAT(parser_value<(ign1 >> ign2)>
                         .is<seq5>);
    EXPECT_THAT(parser_value<(ign2 >> ign1)>
                     .is_not<seq5>);
}

TEST("sequence operator", "non consteval")
{
    (any1 >> any2).parse(TT("abc"));
}



namespace {

template <static_array lhs, static_array rhs>
requires (decltype(like_static_arrays(lhs, rhs))::value)
constexpr auto combine_strings = []
{
    auto str = lhs.template create_empty_with_size<lhs.size() + rhs.size()>();
    auto it = str.begin();
    for (auto c : lhs)
        *it++ = c;
    for (auto c : rhs)
        *it++ = c;

    return str;
}();

template <parser... LHS, parser RHS>
requires (RHS::family != sequence_family)
consteval auto sequence_combined_left(sequence_parser<LHS...>, RHS)
{
    return sequence_parser<LHS..., RHS>{};
}

template <parser LHS, parser... RHS>
requires (LHS::family != sequence_family)
consteval auto sequence_combined_right(LHS, sequence_parser<RHS...>)
{
    return sequence_parser<LHS, RHS...>{};
}

template <parser... LHS, parser... RHS>
consteval auto sequence_combined_both(sequence_parser<LHS...>, sequence_parser<RHS...>)
{
    return sequence_parser<LHS..., RHS...>{};
}

} // namespace



#define SEQUENCE_OPERATOR_ASSERTER(LHS, RHS)                                                        \
    []<parser LLHS, parser RRHS>(LLHS, RRHS) {                                                      \
        if constexpr (not std::same_as<typename LLHS::value_type, typename RRHS::value_type>)       \
        {                                                                                           \
            ASSERT_COMPILE_TIME((not requires { LLHS{} >> RRHS{}; }));                              \
        }                                                                                           \
        else                                                                                        \
        {                                                                                           \
            ASSERT_COMPILE_TIME((requires { { LLHS{} >> RRHS{} } -> k3::tok3n::detail::parser; })); \
            if constexpr (LLHS::family == all_of_family and RRHS::family == all_of_family)          \
            {                                                                                       \
                constexpr auto str = combine_strings<underlying_v<LLHS>, underlying_v<RRHS>>;       \
                EXPECT_THAT(parser_value<(LLHS{} >> RRHS{})>                                        \
                        .DEP_TEMPLATE is<all_of_parser<str>{}>);                                    \
            }                                                                                       \
            else if constexpr (LLHS::family == sequence_family and RRHS::family != sequence_family) \
            {                                                                                       \
                EXPECT_THAT(parser_value<(LLHS{} >> RRHS{})>                                        \
                        .DEP_TEMPLATE is<sequence_combined_left(LLHS{}, RRHS{})>);                  \
            }                                                                                       \
            else if constexpr (LLHS::family != sequence_family and RRHS::family == sequence_family) \
            {                                                                                       \
                EXPECT_THAT(parser_value<(LLHS{} >> RRHS{})>                                        \
                        .DEP_TEMPLATE is<sequence_combined_right(LLHS{}, RRHS{})>);                 \
            }                                                                                       \
            else if constexpr (LLHS::family == sequence_family and RRHS::family == sequence_family) \
            {                                                                                       \
                EXPECT_THAT(parser_value<(LLHS{} >> RRHS{})>                                        \
                        .DEP_TEMPLATE is<sequence_combined_both(LLHS{}, RRHS{})>);                  \
            }                                                                                       \
            else                                                                                    \
            {                                                                                       \
                EXPECT_THAT(parser_value<(LLHS{} >> RRHS{})>                                        \
                        .DEP_TEMPLATE is<(sequence_parser<LLHS, RRHS>{})>);                         \
            }                                                                                       \
        }                                                                                           \
    }(LHS{}, RHS{});

#define SEQUENCE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES \
    (any_of_parser<"abc">) (any_of_parser<"xyz">) (any_of_parser<L"abc">) (any_of_parser<L"xyz">)

TEST("sequence operator", "{anything} >> {anything}")
{
    // Note that all the operations are reimplemented for sequence_checker. This is intentional. That way, there's redundancy in the code.
    // A basic implementation is here, so if/when it gets changed in the library itself, it will be detected here.

    // This works just fine, but it takes forever and may crash your computer. User beware.
    // ASSERT_ALL_SAMPLES_2(SEQUENCE_OPERATOR_ASSERTER);

    ASSERT_SAMPLES_2(SEQUENCE_OPERATOR_ASSERTER, SEQUENCE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES, SEQUENCE_SAMPLES_LIST_DIFFERENT_VALUE_TYPES);

    ASSERT_SAMPLES_2(SEQUENCE_OPERATOR_ASSERTER, BASIC_SAMPLES, BASIC_SAMPLES);
}

} // namespace
} // namespace k3::tok3n::tests
