#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/repeat/Delimit.h>

namespace k3::tok3n::modifiers {

struct delimit_keep final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::delimit_keep;

	template <k3::tok3n::detail::parser P, k3::tok3n::detail::parser_compatible_with<P> D>
	constexpr auto operator()(P, D) const
	{
		return Delimit<P, D, std::true_type>{};
	}

	template <k3::tok3n::detail::parser D>
	struct inner final : k3::tok3n::detail::modifier_base
	{
		static constexpr auto family = k3::tok3n::detail::modifier_family::delimit_keep;

		template <k3::tok3n::detail::parser_compatible_with<D> P>
		constexpr auto operator()(P) const
		{
			return Delimit<P, D, std::true_type>{};
		}
	};

	template <k3::tok3n::detail::parser D>
	constexpr auto operator()(D) const
	{
		return inner<D>{};
	}
};

} // namespace k3::tok3n::modifiers
