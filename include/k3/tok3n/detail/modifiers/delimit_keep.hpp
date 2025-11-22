// Copyright 2023-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_MODIFIERS_DELIMIT_KEEP_HPP
#define K3_TOK3N_DETAIL_MODIFIERS_DELIMIT_KEEP_HPP

#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/parsers/delimit.hpp>

namespace k3::tok3n::detail {

struct delimit_keep_modifier final : modifier_base
{
    static constexpr auto family = modifier_family::delimit_keep;

    template <parser P, parser_compatible_with<P> D>
    constexpr auto operator()(P, D) const
    {
        return delimit_parser<P, D>{};
    }

    template <parser D>
    struct inner final : modifier_base
    {
        static constexpr auto family = modifier_family::delimit_keep;

        template <parser_compatible_with<D> P>
        constexpr auto operator()(P) const
        {
            return delimit_parser<P, D>{};
        }
    };

    template <parser D>
    constexpr auto operator()(D) const
    {
        return inner<D>{};
    }
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_MODIFIERS_DELIMIT_KEEP_HPP
