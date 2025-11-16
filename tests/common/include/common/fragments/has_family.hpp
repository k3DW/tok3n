// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_FRAGMENTS_HAS_FAMILY_HPP
#define K3_TOK3N_TESTS_COMMON_FRAGMENTS_HAS_FAMILY_HPP

#include "framework/assert.hpp"
#include <typeinfo>
#include <k3/tok3n/detail/parser.hpp>

namespace k3::tok3n::tests {

template <detail::parser_family family>
struct has_family_fragment
{
    template <class P>
    void operator()(P) const
    {
        EXPECT_COMPILE_TIME(P::family == family)
            << "`P::family` must be the given `family`.\n"
            << "[\n"
            << "    P         = " << typeid(P).name() << "\n"
            << "    P::family = " << static_cast<int>(P::family) << "\n"
            << "    family    = " << static_cast<int>(family) << "\n"
            << "]";
    }
};
template <detail::parser_family family>
constexpr auto has_family = has_family_fragment<family>{};

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_FRAGMENTS_HAS_FAMILY_HPP
