#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/Defaulted.h>

namespace k3::tok3n::modifiers {

template <DefaultConstructible T>
struct defaulted final : ModifierBase
{
	static constexpr auto family = ModifierFamily::defaulted;

	template <Parser P>
	constexpr auto operator()(P) const
	{
		return aliases::Defaulted<P, T>{};
	}
};

} // namespace k3::tok3n::modifiers
