#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/adaptor/Ignore.h>

namespace k3::tok3n::modifiers {

struct ignore final : ModifierBase
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		if constexpr (P::type == IgnoreFamily)
			return P{};
		else
			return Ignore<P>{};
	}
};

} // namespace k3::tok3n::modifiers
