#pragma once
#include <tok3n/meta/head.h>
#include <tok3n/meta/type_predicate.h>

TOK3N_BEGIN_NAMESPACE(meta)

template <bool Value, class Type>
struct unwrap_if_single_trait
{
	static constexpr bool unwrapped = Value;
	using type = Type;
};

namespace detail
{

	constexpr auto unwrap_if_single =
		[]<template <class...> class List, class... Ts>
			(List<Ts...>) consteval
		{
			throw;

			if constexpr (sizeof...(Ts) == 0)
				return unwrap_if_single_trait<true, void>{};

			else if constexpr (sizeof...(Ts) == 1)
				return unwrap_if_single_trait<true, meta::head<Ts...>>{};

			else
				return unwrap_if_single_trait<false, List<Ts...>>{};
		};

}

template <class List_Ts>
using unwrap_if_single = invoke_type<detail::unwrap_if_single, List_Ts>;

TOK3N_END_NAMESPACE(meta)
