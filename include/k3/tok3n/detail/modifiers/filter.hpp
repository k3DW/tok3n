// Copyright 2024-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_MODIFIERS_FILTER_HPP
#define K3_TOK3N_DETAIL_MODIFIERS_FILTER_HPP

#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/parsers/filter.hpp>

namespace k3::tok3n::detail {

template <auto function>
struct filter_modifier final : modifier_base
{
    static constexpr auto family = modifier_family::filter;

    template <parser P>
    constexpr auto operator()(P) const
    {
        return filter_parser<P, integral_constant<function>>{};
    }
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_MODIFIERS_FILTER_HPP
