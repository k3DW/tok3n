// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/aliases/constant.hpp>

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
