// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_MODIFIERS_DEFAULTED_HPP
#define K3_TOK3N_DETAIL_MODIFIERS_DEFAULTED_HPP

#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/aliases/defaulted.hpp>

namespace k3::tok3n::detail {

template <class T>
requires std::is_default_constructible_v<T>
struct defaulted_modifier final : modifier_base
{
    static constexpr auto family = modifier_family::defaulted;

    template <parser P>
    constexpr auto operator()(P) const
    {
        return defaulted_parser<P, T>{};
    }
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_MODIFIERS_DEFAULTED_HPP
