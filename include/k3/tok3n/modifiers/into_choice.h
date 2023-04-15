#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/compound/Choice.h>
#include <k3/tok3n/parsers/divergent/Into.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

template <class T>
struct into_choice final : ModifierBase
{
	template <Parser... Ps>
	requires (... && constructible::Into<Ps, T>) && (constructible::Choice<Into<Ps, T>...>)
	consteval auto operator()(Ps...) const
	{
		return Choice<Into<Ps, T>...>{};
	}
};

TOK3N_END_NAMESPACE(modifiers)
