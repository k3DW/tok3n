#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/concepts/Modifier.h>
#include <k3/tok3n/concepts/Parser.h>

TOK3N_BEGIN_NAMESPACE(modifiers)

template <Modifier... Ms>
struct multi final : ModifierBase
{
	template <Parser P>
	requires requires { { (P{} % ... % Ms{}) } -> Parser; }
	consteval auto operator()(P) const
	{
		return (P{} % ... % Ms{});
	}
};

TOK3N_END_NAMESPACE(modifiers)
