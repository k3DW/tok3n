#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/parsers/delimit.h>
#include <k3/tok3n/detail/parsers/ignore.h>

namespace k3::tok3n::detail {

struct delimit_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::delimit;

	template <parser P, parser_compatible_with<P> D>
	constexpr auto operator()(P, D) const
	{
		return delimit_parser<P, ignore_parser<D>>{};
	}

	template <parser D>
	struct inner final : modifier_base
	{
		static constexpr auto family = modifier_family::delimit;

		template <parser_compatible_with<D> P>
		constexpr auto operator()(P) const
		{
			return delimit_parser<P, ignore_parser<D>>{};
		}
	};

	template <parser D>
	constexpr auto operator()(D) const
	{
		return inner<D>{};
	}
};

} // namespace k3::tok3n::detail
