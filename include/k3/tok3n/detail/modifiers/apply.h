#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/divergent/ApplyMap.h>

namespace k3::tok3n::detail {

template <auto function>
struct apply_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::apply;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return aliases::ApplyMap<P, integral_constant<function>>{};
	}
};

} // namespace k3::tok3n::detail
