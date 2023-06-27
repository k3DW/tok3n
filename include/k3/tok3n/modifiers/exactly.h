#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/repeat/Exactly.h>

namespace k3::tok3n::modifiers {

template <std::size_t N>
requires (N != 0)
struct exactly final : ModifierBase
{
	template <Parser P>
	requires constructible::Exactly<P, N>
	consteval auto operator()(P) const
	{
		return Exactly<P, N>{};
	}
};

} // namespace k3::tok3n::modifiers
