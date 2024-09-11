#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/parsers/repeat/Delimit.h>

namespace k3::tok3n::modifiers {

struct delimit final : k3::tok3n::detail::modifier_base
{
	static constexpr auto family = k3::tok3n::detail::modifier_family::delimit;

	template <Parser P, ParserCompatibleWith<P> D>
	constexpr auto operator()(P, D) const
	{
		return Delimit<P, D, std::false_type>{};
	}

	template <Parser D>
	struct inner final : k3::tok3n::detail::modifier_base
	{
		static constexpr auto family = k3::tok3n::detail::modifier_family::delimit;

		template <ParserCompatibleWith<D> P>
		constexpr auto operator()(P) const
		{
			return Delimit<P, D, std::false_type>{};
		}
	};

	template <Parser D>
	constexpr auto operator()(D) const
	{
		return inner<D>{};
	}
};

} // namespace k3::tok3n::modifiers
