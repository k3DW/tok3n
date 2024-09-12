#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/parser.h>

namespace k3::tok3n::detail {

template <modifier... Ms>
struct multi_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::multi;

	template <parser P>
	requires requires { { (P{} % ... % Ms{}) } -> parser; }
	constexpr auto operator()(P) const
	{
		return (P{} % ... % Ms{});
	}
};

} // namespace k3::tok3n::detail
