#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/adaptor/Ignore.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

struct ignore final : ModifierBase
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		if constexpr (P::type == IgnoreType)
			return P{};
		else
			return Ignore<P>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)