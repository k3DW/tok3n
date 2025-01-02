// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include <k3/tok3n/detail/modifier.hpp>
#include <k3/tok3n/detail/parsers/join.hpp>

namespace k3::tok3n::detail {

struct join_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::join;

	template <parser P>
	constexpr auto operator()(P) const
	{
		if constexpr (P::family == join_family)
			return P{};
		else
			return join_parser<P>{};
	}
};

} // namespace k3::tok3n::detail
