#pragma once
#include <k3/tok3n/meta/type_list.h>
#include <type_traits>

namespace k3::tok3n::meta {

namespace detail
{

	template <template <class...> class List>
	constexpr auto list_cast =
		[]<class... Ts>
			(type_list<std::type_identity<Ts>...>)
		-> List<Ts...>
		{
			throw;
		};

}

template <template <class...> class List, class type_list_Ts>
using list_cast = invoke_type<detail::list_cast<List>, type_list_Ts>;

static_assert(std::same_as<
	list_cast<std::tuple, type_list<std::type_identity<int>, std::type_identity<double>, std::type_identity<char>>>,
	std::tuple<int, double, char>
>);

static_assert(std::same_as<
	list_cast<std::tuple, type_list<>>,
	std::tuple<>
>);

} // namespace k3::tok3n::meta
