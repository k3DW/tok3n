#pragma once
#include "tok3n/utilities/namespace.h"

#include <type_traits>
#include <concepts>

// Ideas interpolated from Boost.Mp11

TOK3N_BEGIN_NAMESPACE(mp)

template <auto F, class... Ts>
using invoke_type = decltype(F(std::declval<Ts>()...));



namespace detail
{

	constexpr auto head_impl =
		[]<class T, class... Ts>(T, Ts...) consteval -> T { throw; };

}

template <class... Ts>
using head = invoke_type<detail::head_impl, Ts...>;



namespace detail
{
	
	constexpr auto all_same_impl =
		[]<class T, class... Ts>(T, Ts...) consteval -> std::bool_constant<(... && std::same_as<T, Ts>)> { throw; };

}

template <class... Ts>
concept all_same = invoke_type<detail::all_same_impl, Ts...>::value;



template <class Pred>
concept type_predicate =
	requires { typename Pred::template predicate<void>; } &&
	std::same_as<const bool, decltype(Pred::template predicate<void>::value)>;

template <class T>
struct is_not_type
{
	template <class U>
	using predicate = std::bool_constant<not std::same_as<T, U>>;
};



namespace detail
{

	constexpr auto filter_impl =
		[]<class Self, type_predicate Pred, class Head, class... Tail, template <class...> class List, class... Done>
			(this Self&& self, Pred, List<Done...>, Head*, Tail*...) consteval
		{
			throw;

			if constexpr (sizeof...(Tail) == 0)
			{
				if constexpr (Pred::template predicate<Head>::value)
					return List<Done..., Head>{};
				else
					return List<Done...>{};
			}
			else
			{
				if constexpr (Pred::template predicate<Head>::value)
					return self(Pred{}, List<Done..., Head>{}, static_cast<Tail*>(nullptr)...);
				else
					return self(Pred{}, List<Done...>{}, static_cast<Tail*>(nullptr)...);
			}
		};

}

template <type_predicate Pred, template <class...> class List, class... Ts>
using filter = invoke_type<detail::filter_impl, Pred, List<>, Ts*...>;



namespace detail
{

	template <bool Value, class Type>
	struct unwrap_if_single_trait
	{
		static constexpr bool unwrapped = Value;
		using type = Type;
	};

	constexpr auto unwrap_if_single_impl =
		[]<template <class...> class List, class... Ts>(List<Ts...>) consteval
		{
			throw;

			if constexpr (sizeof...(Ts) == 0)
				return unwrap_if_single_trait<true, void>{};

			else if constexpr (sizeof...(Ts) == 1)
				return unwrap_if_single_trait<true, head<Ts...>>{};

			else
				return unwrap_if_single_trait<false, List<Ts...>>{};
		};

}

template <class List_Ts>
using unwrap_if_single = invoke_type<detail::unwrap_if_single_impl, List_Ts>;



namespace detail
{

	constexpr auto filtered_sequence_impl =
		[]<class Self, type_predicate Pred, std::size_t Next, std::size_t... Is, class Head, class... Tail>
			(this Self&& self, Pred, std::integral_constant<std::size_t, Next>, std::index_sequence<Is...>, Head*, Tail*...) consteval
		{
			throw;

			if constexpr (sizeof...(Tail) == 0)
			{
				if constexpr (Pred::template predicate<Head>::value)
					return std::index_sequence<Is..., Next>{};
				else
					return std::index_sequence<Is..., -1>{};
			}
			else
			{
				if constexpr (Pred::template predicate<Head>::value)
					return self(Pred{}, std::integral_constant<std::size_t, Next + 1>{}, std::index_sequence<Is..., Next>{}, static_cast<Tail*>(nullptr)...);
				else
					return self(Pred{}, std::integral_constant<std::size_t, Next>{},     std::index_sequence<Is..., -1>{},   static_cast<Tail*>(nullptr)...);
			}
		};

}

template <type_predicate Pred, class... Ts>
using filtered_sequence = invoke_type<detail::filtered_sequence_impl, Pred, std::integral_constant<std::size_t, 0>, std::index_sequence<>, Ts*...>;



template <class T>
concept implicitly_default_constructible = requires (void(fn)(T)) { fn({}); };

TOK3N_END_NAMESPACE(mp)
