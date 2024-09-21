#pragma once
#include <k3/tok3n/detail/modifier.h>
#include <k3/tok3n/detail/modifiers/name.h>
#include <k3/tok3n/detail/static_array.h>
#include <k3/tok3n/detail/substitution.h>
#include <k3/tok3n/detail/parsers/named.h>

namespace k3::tok3n::detail {

namespace impl {

template <class T, substitution Sub>
requires (not parser<T>)
constexpr auto SubstituteOne(T, Sub)
	-> T;

template <template <static_array> class Basic, static_array arr, substitution Sub>
requires parser<Basic<arr>>
constexpr auto SubstituteOne(Basic<arr>, Sub)
	-> Basic<arr>;

template <parser P, static_array str, substitution Sub>
constexpr parser auto SubstituteOne(named_parser<P, str>, Sub);

template <template <class...> class Template, class... Args, substitution Sub>
requires parser<Template<Args...>>
constexpr parser auto SubstituteOne(Template<Args...>, Sub)
{
	return Template<decltype(SubstituteOne(Args{}, Sub{}))...>{};
}

template <parser P, static_array str, substitution Sub>
constexpr parser auto SubstituteOne(named_parser<P, str>, Sub)
{
	using InnerSubbed = decltype(SubstituteOne(P{}, Sub{}));
	if constexpr (Sub::name == str)
		return Sub::mod(InnerSubbed{});
	else
		return named_parser<InnerSubbed, str>{};
}

template <parser P, substitution Sub, substitution... Subs>
constexpr parser auto Substitute(P, Sub, Subs...)
{
	using Subbed = decltype(SubstituteOne(P{}, Sub{}));
	if constexpr (sizeof...(Subs) == 0)
		return Subbed{};
	else
		return decltype(Substitute(Subbed{}, Subs{}...)){};
}

} // namespace impl

struct sub_modifier final : modifier_base
{
	static constexpr auto family = modifier_family::sub;

	template <parser P, substitution Sub, substitution... Subs>
	constexpr auto operator()(P, Sub, Subs...) const
	{
		return decltype(impl::Substitute(P{}, Sub{}, Subs{}...)){};
	}

	template <substitution Sub, substitution... Subs>
	struct inner final : modifier_base
	{
		static constexpr auto family = modifier_family::sub;

		template <parser P>
		constexpr auto operator()(P) const
		{
			return decltype(impl::Substitute(P{}, Sub{}, Subs{}...)){};
		}
	};

	template <substitution Sub, substitution... Subs>
	constexpr auto operator()(Sub, Subs...) const
	{
		return inner<Sub, Subs...>{};
	}
};

} // namespace k3::tok3n::detail
