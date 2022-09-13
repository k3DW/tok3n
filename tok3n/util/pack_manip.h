#pragma once
#include <type_traits>

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

//template <class List>
//using first_type = typename detail::pack_manip::first_type_impl<List>::type;

template <class... Ts>
using first_type = typename detail::pack_manip::first_type_impl<type_list<Ts...>>::type;

namespace detail::pack_manip
{

	template <class List>
	struct all_same_type_impl {};

	template <class T, class... Ts>
	struct all_same_type_impl<type_list<T, Ts...>> { bool value = (... && std::same_as<T, Ts>); };

}

//template <class List>
//concept all_same_type = detail::pack_manip::all_same_type_impl<List>::value;

template <class... Ts>
concept all_same_type = detail::pack_manip::all_same_type_impl<type_list<Ts...>>::value;

}
