#pragma once
#include <k3/tok3n/detail/invoke_type.h>
#include <k3/tok3n/detail/type_list.h>
#include <type_traits>

namespace k3::tok3n::detail {

template <template <class...> class List>
constexpr auto list_cast_impl =
	[]<class... Ts>
		(type_list<std::type_identity<Ts>...>)
	-> List<Ts...>
	{
		throw;
	};

template <template <class...> class List, class type_list_Ts>
using list_cast = invoke_type<list_cast_impl<List>, type_list_Ts>;

static_assert(std::same_as<
	list_cast<std::tuple, type_list<std::type_identity<int>, std::type_identity<double>, std::type_identity<char>>>,
	std::tuple<int, double, char>
>);

static_assert(std::same_as<
	list_cast<std::tuple, type_list<>>,
	std::tuple<>
>);

} // namespace k3::tok3n::detail
