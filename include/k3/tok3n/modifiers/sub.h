#pragma once
#include <k3/tok3n/types/ModifierBase.h>
#include <k3/tok3n/types/StaticArray.h>
#include <k3/tok3n/types/Substitution.h>
#include <k3/tok3n/parsers/adaptor/Named.h>
#include <k3/tok3n/modifiers/name.h>

namespace k3::tok3n::modifiers {

namespace detail {

template <class T, IsSubstitution Sub>
requires (not Parser<T>)
constexpr auto SubstituteOne(T, Sub)
	-> T;

template <template <StaticArray> class Basic, StaticArray arr, IsSubstitution Sub>
requires Parser<Basic<arr>>
constexpr auto SubstituteOne(Basic<arr>, Sub)
	-> Basic<arr>;

template <Parser P, StaticArray str, IsSubstitution Sub>
constexpr Parser auto SubstituteOne(Named<P, str>, Sub);

template <template <class...> class Template, class... Args, IsSubstitution Sub>
requires Parser<Template<Args...>>
constexpr Parser auto SubstituteOne(Template<Args...>, Sub)
{
	return Template<decltype(SubstituteOne(Args{}, Sub{}))...>{};
}

template <Parser P, StaticArray str, IsSubstitution Sub>
constexpr Parser auto SubstituteOne(Named<P, str>, Sub)
{
	using InnerSubbed = decltype(SubstituteOne(P{}, Sub{}));
	if constexpr (Sub::name == str)
		return Sub::mod(InnerSubbed{});
	else
		return Named<InnerSubbed, str>{};
}

template <Parser P, IsSubstitution Sub, IsSubstitution... Subs>
constexpr Parser auto Substitute(P, Sub, Subs...)
{
	using Subbed = decltype(SubstituteOne(P{}, Sub{}));
	if constexpr (sizeof...(Subs) == 0)
		return Subbed{};
	else
		return decltype(Substitute(Subbed{}, Subs{}...)){};
}

} // namespace detail

struct sub final : ModifierBase
{
	static constexpr auto family = ModifierFamily::sub;

	template <Parser P, IsSubstitution Sub, IsSubstitution... Subs>
	constexpr auto operator()(P, Sub, Subs...) const
	{
		return decltype(detail::Substitute(P{}, Sub{}, Subs{}...)){};
	}

	template <IsSubstitution Sub, IsSubstitution... Subs>
	struct inner final : ModifierBase
	{
		static constexpr auto family = ModifierFamily::sub;

		template <Parser P>
		constexpr auto operator()(P) const
		{
			return decltype(detail::Substitute(P{}, Sub{}, Subs{}...)){};
		}
	};

	template <IsSubstitution Sub, IsSubstitution... Subs>
	constexpr auto operator()(Sub, Subs...) const
	{
		return inner<Sub, Subs...>{};
	}
};

} // namespace k3::tok3n::modifiers
