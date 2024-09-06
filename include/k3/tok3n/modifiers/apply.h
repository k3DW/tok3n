#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/ApplyMap.h>

namespace k3::tok3n::modifiers {

template <auto function>
struct apply final : ModifierBase
{
	static constexpr auto family = ModifierFamily::apply;

	template <Parser P>
	constexpr auto operator()(P) const
	{
		return aliases::ApplyMap<P, detail::integral_constant<function>>{};
	}
};

} // namespace k3::tok3n::modifiers
