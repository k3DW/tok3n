#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/parsers/compound/Choice.h>
#include <k3/tok3n/parsers/divergent/Into.h>

namespace k3::tok3n::modifiers {

template <class T>
struct into_choice final : ModifierBase
{
	template <Parser... Ps>
	requires (... && IntoConstructible<Ps, T>) && (ChoiceConstructible<Into<Ps, T>...>)
	consteval auto operator()(Ps...) const
	{
		return Choice<Into<Ps, T>...>{};
	}
};

} // namespace k3::tok3n::modifiers
