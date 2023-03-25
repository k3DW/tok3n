#pragma once
#include <tok3n/types/ModifierBase.h>
#include <tok3n/parsers/divergent/Transform.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

template <auto function>
struct fn final : ModifierBase
{
	template <Parser P>
	requires detail::Transform_able<P, function>
	consteval auto operator()(P) const
	{
		return Transform<P, function>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)
