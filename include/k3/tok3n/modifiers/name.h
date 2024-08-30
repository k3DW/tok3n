#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/types/StaticArray.h>
#include <k3/tok3n/types/Substitution.h>
#include <k3/tok3n/parsers/adaptor/Named.h>

namespace k3::tok3n::modifiers {

template <StaticArray str>
struct name final : ModifierBase
{
    static constexpr auto family = ModifierFamily::name;

    static constexpr auto Name = str;

    template <Parser P>
    constexpr auto operator()(P) const
    {
        return Named<P, str>{};
    }

    template <Modifier M>
    constexpr auto operator=(M) const
    {
        return Substitution<str, M>{};
    }
};

} // namespace k3::tok3n::modifiers
