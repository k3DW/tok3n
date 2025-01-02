// Copyright 2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/aliases/apply_filter.hpp>

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
