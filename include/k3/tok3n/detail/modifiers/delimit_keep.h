#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/repeat/Delimit.h>

namespace k3::tok3n::detail {

struct delimit_keep_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::delimit_keep;

	template <parser P, parser_compatible_with<P> D>
	constexpr auto operator()(P, D) const
	{
		return Delimit<P, D, std::true_type>{};
	}

	template <parser D>
	struct inner final : modifier_base
	{
		static constexpr auto family = modifier_family::delimit_keep;

		template <parser_compatible_with<D> P>
		constexpr auto operator()(P) const
		{
			return Delimit<P, D, std::true_type>{};
		}
	};

	template <parser D>
	constexpr auto operator()(D) const
	{
		return inner<D>{};
	}
};

} // namespace k3::tok3n::detail
