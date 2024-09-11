#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/adaptor/Ignore.h>

namespace k3::tok3n::modifiers {

struct ignore final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::ignore;

	template <k3::tok3n::detail::parser P>
	constexpr auto operator()(P) const
	{
		if constexpr (P::family == detail::ignore_family)
			return P{};
		else
			return Ignore<P>{};
	}
};

} // namespace k3::tok3n::modifiers
