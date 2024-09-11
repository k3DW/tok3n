#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/parser.h>

namespace k3::tok3n::modifiers {

template <k3::tok3n::detail::modifier... Ms>
struct multi final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::multi;

	template <k3::tok3n::detail::parser P>
	requires requires { { (P{} % ... % Ms{}) } -> k3::tok3n::detail::parser; }
	constexpr auto operator()(P) const
	{
		return (P{} % ... % Ms{});
	}
};

} // namespace k3::tok3n::modifiers
