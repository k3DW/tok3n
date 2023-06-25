#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/Join.h>

namespace k3::tok3n::modifiers {

struct join final : ModifierBase
{
	template <Parser P>
	requires constructible::Join<P>
	consteval auto operator()(P) const
	{
		if constexpr (std::same_as<Input, typename P::result_type>)
			return P{};
		else
			return Join<P>{};
	}
};

} // namespace k3::tok3n::modifiers
