#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/divergent/ApplyInto.h>

namespace k3::tok3n::detail {

template <class T>
struct apply_into_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::apply_into;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return aliases::ApplyInto<P, T>{};
	}
};

} // namespace k3::tok3n::detail
