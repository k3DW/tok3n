#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/Into.h>

namespace k3::tok3n::modifiers {

template <class T>
struct into final : ModifierBase
{
	static constexpr auto family = ModifierFamily::into;

	template <Parser P>
	constexpr auto operator()(P) const
	{
		return Into<P, T>{};
	}
};

} // namespace k3::tok3n::modifiers
