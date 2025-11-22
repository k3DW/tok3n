// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_SUCCEEDS_PARSING_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_SUCCEEDS_PARSING_HPP

#include "framework/assert.hpp"
#include <concepts>
#include <typeinfo>
#include <k3/tok3n/detail/parser.hpp>

namespace k3::tok3n::tests {

template <std::invocable<> InputFn, std::invocable<> ResultFn, std::invocable<> RemainingFn>
struct succeeds_parsing_fragment
{
    constexpr succeeds_parsing_fragment() = default;
    constexpr succeeds_parsing_fragment(InputFn, ResultFn, RemainingFn) {}

    template <class P>
    void operator()(P) const
    {
        // Todo: Improve the streamed out error messages

        EXPECT_COMPILE_AND_RUN_TIME(P::parse(InputFn{}()).has_value())
            // << "`P` could not parse the given input.\n"
            // << "[\n"
            // << "    P     = " << typeid(P).name() << "\n"
            // << "    input = \"" << InputFn{}() << "\"\n"
            // << "]";
            << "`P` could not parse the given input.\n";

        // The following EXPECT depends on the previous EXPECT,
        // and therefore this `if constexpr` is here so the code always compiles.
        constexpr bool has_value = P::parse(InputFn{}()).has_value();
        if constexpr (has_value and not std::same_as<decltype(ResultFn{}()), void>)
        {
            EXPECT_COMPILE_AND_RUN_TIME(*P::parse(InputFn{}()) == ResultFn{}())
                // << "`*P::parse(input)` must be the same as the given `result`.\n"
                // << "[\n"
                // << "    P                 = " << typeid(P).name() << "\n"
                // << "    input             = \"" << InputFn{}() << "\"\n"
                // << "    *P::parse(input)  = \"" << *(P::parse(InputFn{}())) << "\"\n"
                // << "    result            = \"" << ResultFn{}() << "\"\n"
                // << "]";
                << "`*P::parse(input)` must be the same as the given `result`.";
        }

        EXPECT_COMPILE_AND_RUN_TIME(P::parse(InputFn{}()).remaining() == RemainingFn{}())
            // << "`P::parse(input).remaining()` must be the same as the given `remaining`.\n"
            // << "[\n"
            // << "    P                           = " << typeid(P).name() << "\n"
            // << "    input                       = \"" << InputFn{}() << "\"\n"
            // << "    P::parse(input).remaining() = \"" << (P::parse(InputFn{}())).remaining() << "\"\n"
            // << "    remaining                   = \"" << RemainingFn{}() << "\"\n"
            // << "]";
            << "`P::parse(input).remaining()` must be the same as the given `remaining`.";

        EXPECT_COMPILE_AND_RUN_TIME(P::lookahead(InputFn{}()).has_value())
            // << "`P` could not lookahead the given input.\n"
            // << "[\n"
            // << "    P     = " << typeid(P).name() << "\n"
            // << "    input = \"" << InputFn{}() << "\"\n"
            // << "]";
            << "`P` could not lookahead the given input.\n";

        EXPECT_COMPILE_AND_RUN_TIME(P::lookahead(InputFn{}()).remaining() == RemainingFn{}())
            // << "`P::lookahead(input).remaining()` must be the same as the given `remaining`.\n"
            // << "[\n"
            // << "    P                               = " << typeid(P).name() << "\n"
            // << "    input                           = \"" << InputFn{}() << "\"\n"
            // << "    P::lookahead(input).remaining() = \"" << (P::lookahead(InputFn{}())).remaining() << "\"\n"
            // << "    remaining                       = \"" << RemainingFn{}() << "\"\n"
            // << "]";
            << "`P::lookahead(input).remaining()` must be the same as the given `remaining`.";
    }
};
template <std::invocable<> InputFn, std::invocable<> ResultFn, std::invocable<> RemainingFn>
succeeds_parsing_fragment(InputFn, ResultFn, RemainingFn) -> succeeds_parsing_fragment<InputFn, ResultFn, RemainingFn>;

#define SUCCEEDS_PARSING(INPUT, RESULT, REMAINING)  \
    (::k3::tok3n::tests::succeeds_parsing_fragment{ \
        ([]() constexpr { return INPUT; }),         \
        ([]() constexpr { return RESULT; }),        \
        ([]() constexpr { return REMAINING; })      \
    })

#define SUCCEEDS_PARSING_VOID(INPUT, REMAINING)     \
    (::k3::tok3n::tests::succeeds_parsing_fragment{ \
        ([]() constexpr { return INPUT; }),         \
        ([]{}),                                     \
        ([]() constexpr { return REMAINING; })      \
    })

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_SUCCEEDS_PARSING_HPP
