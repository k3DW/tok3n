// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_FAILS_PARSING_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_FAILS_PARSING_HPP

#include "framework/assert.hpp"
#include <concepts>
#include <typeinfo>
#include <k3/tok3n/detail/parser.hpp>

namespace k3::tok3n::tests {

template <std::invocable<> auto InputFn>
struct fails_parsing_fragment
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
            // << "`P::parse(input).remaining()` must be the same as the given `input`."
            // << "[\n"
            // << "    P                           = " << typeid(P).name() << "\n"
            // << "    input                       = \"" << InputFn() << "\"\n"
            // << "    P::parse(input).remaining() = \"" << (P::parse(InputFn())).remaining() << "\"\n"
            // << "]";
            << "`P::parse(input).remaining()` must be the same as the given `input`.";

        EXPECT_COMPILE_AND_RUN_TIME(not P::lookahead(InputFn()).has_value())
            // << "`P` could lookahead the given input, but should not.\n"
            // << "[\n"
            // << "    P     = " << typeid(P).name() << "\n"
            // << "    input = \"" << InputFn() << "\"\n"
            // << "]";
            << "`P` could lookahead the given input, but should not.\n";

        EXPECT_COMPILE_AND_RUN_TIME(P::lookahead(InputFn()).remaining() == InputFn())
            // << "`P::lookahead(input).remaining()` must be the same as the given `input`."
            // << "[\n"
            // << "    P                               = " << typeid(P).name() << "\n"
            // << "    input                           = \"" << InputFn() << "\"\n"
            // << "    P::lookahead(input).remaining() = \"" << (P::lookahead(InputFn())).remaining() << "\"\n"
            // << "]";
            << "`P::lookahead(input).remaining()` must be the same as the given `input`.";
    }
};
template <std::invocable<> auto InputFn>
constexpr auto fails_parsing = fails_parsing_fragment<InputFn>{};

#define FAILS_PARSING(INPUT) \
    (::k3::tok3n::tests::fails_parsing<[]() constexpr { return INPUT; }>)

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_FAILS_PARSING_HPP
