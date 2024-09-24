#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/aliases/apply_filter.h>

namespace k3::tok3n::detail {

template <auto function>
struct apply_filter_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::apply_filter;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return apply_filter_parser<P, integral_constant<function>>{};
	}
};

} // namespace k3::tok3n::detail
