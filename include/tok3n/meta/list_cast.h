#pragma once
#include <tok3n/meta/type_list.h>
#include <type_traits>

TOK3N_BEGIN_NAMESPACE(meta)

namespace impl
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
using list_cast = invoke_type<impl::list_cast<List>, type_list_Ts>;

static_assert(std::same_as<
	list_cast<std::tuple, type_list<std::type_identity<int>, std::type_identity<double>, std::type_identity<char>>>,
	std::tuple<int, double, char>
>);

static_assert(std::same_as<
	list_cast<std::tuple, type_list<>>,
	std::tuple<>
>);

TOK3N_END_NAMESPACE(meta)