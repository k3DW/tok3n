// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_SUCCEEDS_LOOKAHEAD_ONLY_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_SUCCEEDS_LOOKAHEAD_ONLY_HPP

#include "framework/assert.hpp"
#include <concepts>
#include <typeinfo>
#include <k3/tok3n/detail/parser.hpp>

namespace k3::tok3n::tests {

template <std::invocable<> auto InputFn, std::invocable<> auto RemainingFn>
struct succeeds_lookahead_only_fragment
{
    template <class P>
    void operator()(P) const
    {
        // Todo: Improve the streamed out error messages

        EXPECT_COMPILE_AND_RUN_TIME(not P::parse(InputFn()).has_value())
            // << "`P` could parse the given input, but should not.\n"
            // << "[\n"
            // << "    P     = " << typeid(P).name() << "\n"
            // << "    input = \"" << InputFn() << "\"\n"
            // << "]";
            << "`P` could parse the given input, but should not.\n";

        EXPECT_COMPILE_AND_RUN_TIME(P::parse(InputFn()).remaining() == InputFn())
            // << "`P::parse(input).remaining()` must be the same as the given `input`.\n"
            // << "[\n"
            // << "    P                           = " << typeid(P).name() << "\n"
            // << "    input                       = \"" << InputFn() << "\"\n"
            // << "    P::parse(input).remaining() = \"" << (P::parse(InputFn())).remaining() << "\"\n"
            // << "]";
            << "`P::parse(input).remaining()` must be the same as the given `input`.";

        EXPECT_COMPILE_AND_RUN_TIME(P::lookahead(InputFn()).has_value())
            // << "`P` could not lookahead the given input.\n"
            // << "[\n"
            // << "    P     = " << typeid(P).name() << "\n"
            // << "    input = \"" << InputFn() << "\"\n"
            // << "]";
            << "`P` could not lookahead the given input.\n";

        EXPECT_COMPILE_AND_RUN_TIME(P::lookahead(InputFn()).remaining() == RemainingFn())
            // << "`P::lookahead(input).remaining()` must be the same as the given `remaining`.\n"
            // << "[\n"
            // << "    P                               = " << typeid(P).name() << "\n"
            // << "    input                           = \"" << InputFn() << "\"\n"
            // << "    P::lookahead(input).remaining() = \"" << (P::lookahead(InputFn())).remaining() << "\"\n"
            // << "    remaining                       = \"" << RemainingFn() << "\"\n"
            // << "]";
            << "`P::lookahead(input).remaining()` must be the same as the given `remaining`.";
    }
};
template <std::invocable<> auto InputFn, std::invocable<> auto RemainingFn>
constexpr auto succeeds_lookahead_only = succeeds_lookahead_only_fragment<InputFn, RemainingFn>{};

#define SUCCEEDS_LOOKAHEAD_ONLY(INPUT, REMAINING) \
    (::k3::tok3n::tests::succeeds_lookahead_only< \
        [&]() constexpr { return INPUT; },        \
        [&]() constexpr { return REMAINING; }     \
    >)

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_SUCCEEDS_LOOKAHEAD_ONLY_HPP
