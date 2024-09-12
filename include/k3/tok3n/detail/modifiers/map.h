#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/divergent/Map.h>

namespace k3::tok3n::detail {

template <auto function>
struct map_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::map;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return Map<P, integral_constant<function>>{};
	}
};

} // namespace k3::tok3n::detail
