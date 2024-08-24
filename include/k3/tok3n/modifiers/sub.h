#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/types/StaticArray.h>
#include <k3/tok3n/types/Substitution.h>
#include <k3/tok3n/parsers/adaptor/Named.h>

namespace k3::tok3n::modifiers {

struct sub final : ModifierBase
{
	static constexpr auto family = ModifierFamily::sub;

	template <Parser P, IsSubstitution Sub, IsSubstitution... Subs>
	constexpr auto operator()(P, Sub, Subs...) const
	{
		return 0; // TODO
	}

	template <IsSubstitution Sub, IsSubstitution... Subs>
	struct inner final : ModifierBase
	{
		static constexpr auto family = ModifierFamily::sub;

		template <Parser P>
		constexpr auto operator()(P) const
		{
			return 1; // TODO
		}
	};

	template <IsSubstitution Sub, IsSubstitution... Subs>
	constexpr auto operator()(Sub, Subs...) const
	{
		return inner<Sub, Subs...>{};
	}
};

} // namespace k3::tok3n::modifiers
