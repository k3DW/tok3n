#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/Map.h>

namespace k3::tok3n::modifiers {

template <auto function>
struct map final : ModifierBase
{
	static constexpr auto family = ModifierFamily::map;

	template <Parser P>
	constexpr auto operator()(P) const
	{
		return Map<P, Const<function>>{};
	}
};

} // namespace k3::tok3n::modifiers
