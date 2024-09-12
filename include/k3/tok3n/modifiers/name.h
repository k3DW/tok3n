#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/static_array.h>
#include <k3/tok3n/detail/substitution.h>
#include <k3/tok3n/parsers/adaptor/Named.h>

namespace k3::tok3n::modifiers {

template <k3::tok3n::detail::static_array str>
struct name final : k3::tok3n::detail::modifier_base
{
    static constexpr auto family = k3::tok3n::detail::modifier_family::name;

    static constexpr auto Name = str;

    template <k3::tok3n::detail::parser P>
    constexpr auto operator()(P) const
    {
        return Named<P, str>{};
    }

    template <k3::tok3n::detail::modifier M>
    constexpr auto operator=(M) const
    {
        return k3::tok3n::detail::substitution_info<str, M>{};
    }
};

} // namespace k3::tok3n::modifiers
