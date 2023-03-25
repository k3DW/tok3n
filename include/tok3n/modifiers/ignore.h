#pragma once
#include <tok3n/types/ModifierBase.h>
#include <tok3n/parsers/adaptor/Ignore.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

struct ignore final : ModifierBase
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		if constexpr (IsIgnore<P>)
			return P{};
		else
			return Ignore<P>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)
