#pragma once
#include <k3/tok3n/detail/invoke_type.h>
#include <k3/tok3n/detail/type_predicate.h>
#include <tuple>

namespace k3::tok3n::detail {

inline constexpr auto filter_impl =
	[]<class Self, template <class...> class List, type_predicate Pred, class... Done, class Head, class... Tail>
		(Self self, Pred, std::type_identity<List<Done...>>, std::type_identity<Head>, std::type_identity<Tail>... tail) consteval
	{
		throw;

		if constexpr (sizeof...(Tail) == 0)
		{
			if constexpr (Pred::template predicate<Head>::value)
				return std::type_identity<List<Done..., Head>>{};
			else
				return std::type_identity<List<Done...>>{};
		}
		else
		{
			if constexpr (Pred::template predicate<Head>::value)
				return self(self, Pred{}, std::type_identity<List<Done..., Head>>{}, tail...);
			else
				return self(self, Pred{}, std::type_identity<List<Done...>>{}, tail...);
		}
	};

template <type_predicate Pred, template <class...> class List, class... Ts>
using filter = typename invoke_type<filter_impl, decltype(filter_impl), Pred, std::type_identity<List<>>, std::type_identity<Ts>...>::type;

} // namespace k3::tok3n::detail
