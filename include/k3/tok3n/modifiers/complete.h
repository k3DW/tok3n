#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/adaptor/Complete.h>

namespace k3::tok3n::modifiers {

struct complete final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::complete;

	template <Parser P>
	constexpr auto operator()(P) const
	{
		if constexpr (P::family == CompleteFamily)
			return P{};
		else
			return Complete<P>{};
	}
};

} // namespace k3::tok3n::modifiers
