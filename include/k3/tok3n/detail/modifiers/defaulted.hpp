// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/aliases/defaulted.hpp>

namespace k3::tok3n::detail {

template <class T>
requires std::is_default_constructible_v<T>
struct defaulted_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::defaulted;

	template <parser P>
	constexpr auto operator()(P) const
	{
		return defaulted_parser<P, T>{};
	}
};

} // namespace k3::tok3n::detail
