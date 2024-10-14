// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/aliases/apply_map.h>

namespace k3::tok3n::detail {

template <auto function>
struct apply_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::apply;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return apply_map_parser<P, integral_constant<function>>{};
	}
};

} // namespace k3::tok3n::detail
