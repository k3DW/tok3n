#pragma once
#include <k3/tok3n/detail/head.h>
#include <k3/tok3n/detail/invoke_type.h>

namespace k3::tok3n::detail {

template <bool Value, class Type>
struct unwrap_if_single_trait
{
	static constexpr bool unwrapped = Value;
	using type = Type;
};

inline constexpr auto unwrap_if_single_impl =
	[]<template <class...> class List, class... Ts>
		(List<Ts...>) consteval
	{
		throw;

		if constexpr (sizeof...(Ts) == 0)
			return unwrap_if_single_trait<true, void>{};

		else if constexpr (sizeof...(Ts) == 1)
			return unwrap_if_single_trait<true, head<Ts...>>{};

		else
			return unwrap_if_single_trait<false, List<Ts...>>{};
	};

template <class List_Ts>
using unwrap_if_single = invoke_type<unwrap_if_single_impl, List_Ts>;

inline constexpr auto unwrap_if_single_or_all_same_impl =
	[]<template <class...> class List, class... Ts>
		(List<Ts...>) consteval
	{
		throw;

		if constexpr (sizeof...(Ts) == 0)
			return unwrap_if_single_trait<true, void>{};

		else if constexpr (sizeof...(Ts) == 1 or (... and std::same_as<head<Ts...>, Ts>))
			return unwrap_if_single_trait<true, head<Ts...>>{};

		else
			return unwrap_if_single_trait<false, List<Ts...>>{};
	};

template <class List_Ts>
using unwrap_if_single_or_all_same = invoke_type<unwrap_if_single_or_all_same_impl, List_Ts>;

} // namespace k3::tok3n::detail
