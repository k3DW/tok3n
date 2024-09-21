#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/aliases/constant.h>

namespace k3::tok3n::detail {

template <auto value>
struct constant_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::constant;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return constant_parser<P, integral_constant<value>>{};
	}
};

} // namespace k3::tok3n::detail
