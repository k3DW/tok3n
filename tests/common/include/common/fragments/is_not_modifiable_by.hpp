// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_IS_NOT_MODIFIABLE_BY_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_IS_NOT_MODIFIABLE_BY_HPP

#include <typeinfo>
#include <k3/k3tchup/assert.hpp>
#include <k3/tok3n/detail/modifier.hpp>

namespace k3::tok3n::tests {

template <detail::modifier auto m>
struct is_not_modifiable_by_fragment
{
    template <detail::parser P>
    void operator()(P) const
    {
        using M = std::remove_cvref_t<decltype(m)>;

        EXPECT_COMPILE_TIME(not requires { m(P{}); })
            << "`M{}(P{})` is a valid expression, but should not be."
            << "[\n"
            << "    P = " << typeid(P).name() << "\n"
            << "    M = " << typeid(M).name() << "\n"
            << "]";

        EXPECT_COMPILE_TIME(not requires { P{} % m; })
            << "`P{} % M{}` is a valid expression, but should not be."
            << "[\n"
            << "    P = " << typeid(P).name() << "\n"
            << "    M = " << typeid(M).name() << "\n"
            << "]";
    }
};
template <detail::modifier auto M>
constexpr auto is_not_modifiable_by = is_not_modifiable_by_fragment<M>{};

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_IS_NOT_MODIFIABLE_BY_HPP
