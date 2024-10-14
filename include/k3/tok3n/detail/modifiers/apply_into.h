// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/aliases/apply_into.h>

namespace k3::tok3n::detail {

template <class T>
struct apply_into_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::apply_into;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return apply_into_parser<P, T>{};
	}
};

} // namespace k3::tok3n::detail
