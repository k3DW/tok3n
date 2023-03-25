#pragma once
#include <tok3n/types/ModifierBase.h>
#include <tok3n/parsers/divergent/ApplyInto.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

template <class T>
struct apply_into final : ModifierBase
{
	template <Parser P>
	requires detail::ApplyInto_able<P, T>
	consteval auto operator()(P) const
	{
		return ApplyInto<P, T>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)
