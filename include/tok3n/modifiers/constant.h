#pragma once
#include <tok3n/types/ModifierBase.h>
#include <tok3n/parsers/divergent/Constant.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

template <auto value>
struct constant final : ModifierBase
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Constant<P, value>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)
