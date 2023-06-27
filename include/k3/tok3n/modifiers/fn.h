#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/Transform.h>

namespace k3::tok3n::modifiers {

template <auto function>
struct fn final : ModifierBase
{
	template <Parser P>
	requires constructible::Transform<P, function>
	consteval auto operator()(P) const
	{
		return Transform<P, function>{};
	}
};

} // namespace k3::tok3n::modifiers
