#pragma once
#include <type_traits>
#include <concepts>

// Ideas mostly taken from Boost.Mp11

namespace k3::mp
{



template <class... Ts>
struct type_list {};



namespace detail
{

	template <class List>
	struct head_impl {};

	template <class T, class... Ts>
	struct head_impl<type_list<T, Ts...>> { using type = T; };

}

template <class... Ts>
using head = typename detail::head_impl<type_list<Ts...>>::type;



namespace detail
{

	template <class List>
	struct all_same_impl {};
	
	template <class T, class... Ts>
	struct all_same_impl<type_list<T, Ts...>>
	{
		static constexpr bool value = (... && std::same_as<T, Ts>);
	};

}

template <class... Ts>
concept all_same = detail::all_same_impl<type_list<Ts...>>::value;



namespace detail
{

	template <class T, class List>
	struct append_impl {};

	template <class T, template <class...> class ListTemplate, class... Ts>
	struct append_impl<T, ListTemplate<Ts...>>
	{
		using type = ListTemplate<T, Ts...>;
	};

}

template <class Head, class List>
using append = typename detail::append_impl<Head, List>::type;



template <class Pred>
concept type_predicate =
	requires { Pred::template predicate; } &&
	not requires { typename Pred::predicate; } &&
	std::same_as<const bool, decltype(Pred::template predicate<void>::value)>;

template <class T>
struct is_not_type
{
	template <class U>
	using predicate = std::bool_constant<not std::same_as<T, U>>;
};



namespace detail
{

	template <type_predicate Pred, class... Ts>
	struct filter_impl {};

	template <type_predicate Pred>
	struct filter_impl<Pred>
	{
		using type = type_list<>;
	};

	template <type_predicate Pred, class Head, class... Tail>
	struct filter_impl<Pred, Head, Tail...>
	{
		using type = std::conditional_t<
			Pred::template predicate<Head>::value,
			append<Head, typename filter_impl<Pred, Tail...>::type>,
			typename filter_impl<Pred, Tail...>::type
		>;
	};

}

template <type_predicate Pred, class... Ts>
using filter = typename detail::filter_impl<Pred, Ts...>::type;



namespace detail
{

	template <class List, template <class...> class NewTemplate>
	struct retarget_impl {};

	template <template <class...> class OldTemplate, template <class...> class NewTemplate, class... Ts>
	struct retarget_impl<OldTemplate<Ts...>, NewTemplate>
	{
		using type = NewTemplate<Ts...>;
	};

}

template <class List, template <class...> class NewTemplate>
using retarget = typename detail::retarget_impl<List, NewTemplate>::type;



template <class List>
struct flatten_if_single {};

template <template <class...> class Template, class T, class... Ts>
struct flatten_if_single<Template<T, Ts...>>
{
	static constexpr bool value = sizeof...(Ts) == 0;
	using type = std::conditional_t<value, T, Template<T, Ts...>>;
};



namespace detail
{

	template <type_predicate Pred, std::size_t NextUp, class Seq, class... Ts>
	struct filtered_sequence_impl {};

	template <type_predicate Pred, std::size_t NextUp, class Seq>
	struct filtered_sequence_impl<Pred, NextUp, Seq>
	{
		using type = Seq;
	};

	template <type_predicate Pred, std::size_t NextUp, std::size_t... Is, class Head, class... Tail>
	struct filtered_sequence_impl<Pred, NextUp, std::index_sequence<Is...>, Head, Tail...>
	{
		using type = std::conditional_t<
			Pred::template predicate<Head>::value,
			typename filtered_sequence_impl<Pred, NextUp + 1, std::index_sequence<Is..., NextUp>, Tail...>::type,
			typename filtered_sequence_impl<Pred, NextUp,     std::index_sequence<Is..., -1>,     Tail...>::type
		>;
	};

}

template <type_predicate Pred, class... Ts>
using filtered_sequence = typename detail::filtered_sequence_impl<Pred, 0, std::index_sequence<>, Ts...>::type;



}
