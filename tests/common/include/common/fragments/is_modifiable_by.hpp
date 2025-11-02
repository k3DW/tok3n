// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_IS_MODIFIABLE_BY_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_IS_MODIFIABLE_BY_HPP

#include "framework/assert.hpp"
#include "common/fragments/parser_value.hpp"
#include <typeinfo>
#include <k3/tok3n/detail/modifier.hpp>

namespace k3::tok3n::tests {

template <detail::modifier M>
struct is_modifiable_by_fragment
{
    template <detail::parser R>
    struct with_result_fragment
    {
        template <detail::parser P>
        void operator()(P) const
        {
            EXPECT_COMPILE_TIME(requires { M{}(P{}); })
                << "`M{}(P{})` is not a valid expression"
                << "[\n"
                << "    P = " << typeid(P).name() << "\n"
                << "    M = " << typeid(M).name() << "\n"
                << "]";
            EXPECT_COMPILE_TIME(requires { { M{}(P{}) } -> detail::parser; })
                << "`M{}(P{})` does not result in a parser"
                << "[\n"
                << "    P    = " << typeid(P).name() << "\n"
                << "    M    = " << typeid(M).name() << "\n"
                << "    M(P) = " << typeid(decltype(M{}(P{}))).name() << "\n"
                << "]";

            EXPECT_COMPILE_TIME(requires { P{} % M{}; })
                << "`P{} % M{}` is not a valid expression"
                << "[\n"
                << "    P = " << typeid(P).name() << "\n"
                << "    M = " << typeid(M).name() << "\n"
                << "]";
            EXPECT_COMPILE_TIME(requires { { P{} % M{} } -> detail::parser; })
                << "`P{} % M{}` does not result in a parser"
                << "[\n"
                << "    P     = " << typeid(P).name() << "\n"
                << "    M     = " << typeid(M).name() << "\n"
                << "    P % M = " << typeid(decltype(P{} % M{})).name() << "\n"
                << "]";

            EXPECT_THAT(parser_value<M{}(P{})>.is<R{}>);
        }
    };
    template <detail::parser R>
    static constexpr auto with_result = with_result_fragment<R>{};
};
template <detail::modifier auto m>
constexpr auto is_modifiable_by = is_modifiable_by_fragment<std::remove_cvref_t<decltype(m)>>{};

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_IS_MODIFIABLE_BY_HPP
