// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/static_array.h>
#include <k3/tok3n/detail/substitution.h>
#include <k3/tok3n/detail/parsers/named.h>

namespace k3::tok3n::detail {

template <static_array str>
struct name_modifier final : modifier_base
{
    static constexpr auto family = modifier_family::name;

    static constexpr auto Name = str;

    template <parser P>
    constexpr auto operator()(P) const
    {
        return named_parser<P, str>{};
    }

    template <modifier M>
    constexpr auto operator=(M) const
    {
        return substitution_info<str, M>{};
    }
};

} // namespace k3::tok3n::detail
