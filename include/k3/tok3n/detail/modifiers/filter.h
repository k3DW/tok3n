#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/parsers/filter.h>

namespace k3::tok3n::detail {

template <auto function>
struct filter_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::filter;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return filter_parser<P, integral_constant<function>>{};
	}
};

} // namespace k3::tok3n::detail
