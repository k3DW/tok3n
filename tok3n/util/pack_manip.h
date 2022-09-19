#pragma once
#include <type_traits>
#include <concepts>

// Ideas mostly taken from Boost.Mp11

namespace k3
{

template <class... Ts>
struct type_list {};

namespace detail::pack_manip
{

	template <class List>
	struct first_type_impl {};

	template <class T, class... Ts>
	struct first_type_impl<type_list<T, Ts...>> { using type = T; };

}

template <class... Ts>
using first_type = typename detail::pack_manip::first_type_impl<type_list<Ts...>>::type;

namespace detail::pack_manip
{

	template <class List>
	struct all_same_type_impl {};
	
	template <class T, class... Ts>
	struct all_same_type_impl<type_list<T, Ts...>> { static constexpr bool value = (... && std::same_as<T, Ts>); };

}

template <class... Ts>
concept all_same_type = detail::pack_manip::all_same_type_impl<type_list<Ts...>>::value;



template <class T, class List> struct append;
template <class T, class List> using append_type = typename append<T, List>::type;

template <class T, template <class...> class ListTemplate, class... Ts>
struct append<T, ListTemplate<Ts...>>
{
	using type = ListTemplate<T, Ts...>;
};



template <template <class> class Pred, class... Ts> struct filter;

template <template <class> class Pred>
struct filter<Pred>
{
	using type = type_list<>;
};

template <template <class> class Pred, class Head, class... Tail>
struct filter<Pred, Head, Tail...>
{
	using type = std::conditional_t<
		Pred<Head>::value,
		append_type<Head, typename filter<Pred, Tail...>::type>,
		typename filter<Pred, Tail...>::type
	>;
};



template <class List, template <class...> class NewTemplate> struct retarget;
template <class List, template <class...> class NewTemplate> using retarget_type = typename retarget<List, NewTemplate>::type;

template <template <class...> class OldTemplate, template <class...> class NewTemplate, class... Ts>
struct retarget<OldTemplate<Ts...>, NewTemplate>
{
	using type = NewTemplate<Ts...>;
};

template <template <class...> class Container, template <class> class Pred, class... Ts> using filter_type = retarget_type<typename filter<Pred, Ts...>::type, Container>;


template <template <class> class Pred, std::size_t NextUp, class Seq, class... Ts> struct filtered_index_sequence;
template <template <class> class Pred, class... Ts> using filtered_index_sequence_type = typename filtered_index_sequence<Pred, 0, std::index_sequence<>, Ts...>::type;

template <template <class> class Pred, std::size_t NextUp, class Seq>
struct filtered_index_sequence<Pred, NextUp, Seq>
{
	using type = Seq;
};

template <template <class> class Pred, std::size_t NextUp, std::size_t... Is, class Head, class... Tail>
struct filtered_index_sequence<Pred, NextUp, std::index_sequence<Is...>, Head, Tail...>
{
	using type = std::conditional_t<
		Pred<Head>::value,
		typename filtered_index_sequence<Pred, NextUp + 1, std::index_sequence<Is..., NextUp>, Tail...>::type,
		typename filtered_index_sequence<Pred, NextUp,     std::index_sequence<Is..., -1>,     Tail...>::type
	>;
};



template <class List>
struct flatten_if_single;

template <template <class...> class Template, class T, class... Ts>
struct flatten_if_single<Template<T, Ts...>>
{
	static constexpr bool value = sizeof...(Ts) == 0;

	using type = std::conditional_t<value, T, Template<T, Ts...>>;
};

}
