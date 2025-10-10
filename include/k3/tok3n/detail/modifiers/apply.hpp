// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_MODIFIERS_APPLY_HPP
#define K3_TOK3N_DETAIL_MODIFIERS_APPLY_HPP

#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/aliases/apply_map.hpp>

namespace k3::tok3n::detail {

template <auto function>
struct apply_modifier final : modifier_base
{
    static constexpr auto family = modifier_family::apply;

    template <parser P>
    constexpr auto operator()(P) const
    {
        return apply_map_parser<P, integral_constant<function>>{};
    }
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_MODIFIERS_APPLY_HPP
