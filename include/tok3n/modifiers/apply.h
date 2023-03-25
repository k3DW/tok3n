#pragma once
#include <tok3n/types/ModifierBase.h>
#include <tok3n/parsers/divergent/ApplyTransform.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

template <auto function>
struct apply final : ModifierBase
{
	template <Parser P>
	requires detail::ApplyTransform_able<P, function>
	consteval auto operator()(P) const
	{
		return ApplyTransform<P, function>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)
