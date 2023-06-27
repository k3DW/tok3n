#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/divergent/ApplyTransform.h>

namespace k3::tok3n::modifiers {

template <auto function>
struct apply final : ModifierBase
{
	template <Parser P>
	requires ApplyTransformConstructible<P, function>
	consteval auto operator()(P) const
	{
		return ApplyTransform<P, function>{};
	}
};

} // namespace k3::tok3n::modifiers
