// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/parsers/ignore.h>

namespace k3::tok3n::detail {

struct ignore_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::ignore;

	template <parser P>
	constexpr auto operator()(P) const
	{
		if constexpr (P::family == ignore_family)
			return P{};
		else
			return ignore_parser<P>{};
	}
};

} // namespace k3::tok3n::detail
