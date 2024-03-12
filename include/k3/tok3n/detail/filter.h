#pragma once
#include <k3/tok3n/detail/invoke_type.h>
#include <k3/tok3n/detail/type_predicate.h>
#include <tuple>

namespace k3::tok3n::detail {

template <type_predicate Pred, class ListOfDone, class Head, class... Tail>
struct filter_impl {};

template <type_predicate Pred, template <class...> class List, class... Done, class Head>
struct filter_impl<Pred, List<Done...>, Head>
{
	using type = std::conditional_t<Pred::template predicate<Head>::value,
		List<Done..., Head>,
		List<Done...>
	>;
};

template <type_predicate Pred, template <class...> class List, class... Done, class Head, class... Tail>
struct filter_impl<Pred, List<Done...>, Head, Tail...>
{
	using type = std::conditional_t<Pred::template predicate<Head>::value,
		typename filter_impl<Pred, List<Done..., Head>, Tail...>::type,
		typename filter_impl<Pred, List<Done...>, Tail...>::type
	>;
};

template <type_predicate Pred, template <class...> class List, class... Ts>
using filter = typename filter_impl<Pred, List<>, Ts...>::type;

} // namespace k3::tok3n::detail
