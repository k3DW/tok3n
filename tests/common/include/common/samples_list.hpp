// Copyright 2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_TESTS_COMMON_SAMPLES_LIST_HPP
#define K3_TOK3N_TESTS_COMMON_SAMPLES_LIST_HPP

#include <k3/tok3n/detail/parser.hpp>

namespace k3::tok3n::tests {

template <detail::parser... Ps>
struct parser_list_t {};

template <class... LHS, class... RHS>
constexpr auto operator+(parser_list_t<LHS...>, parser_list_t<RHS...>)
{
    return parser_list_t<LHS..., RHS...>{};
}

template <class...>
inline constexpr auto samples_list = 0; // Must be specialized later

} // namespace k3::tok3n::tests

#endif // K3_TOK3N_TESTS_COMMON_SAMPLES_LIST_HPP
