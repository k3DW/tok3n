#pragma once
#include <k3/tok3n/detail/invoke_type.h>
#include <k3/tok3n/detail/type_predicate.h>
#include <k3/tok3n/detail/list_cast.h>
#include <k3/tok3n/detail/is_not_type.h>
#include <tuple>

namespace k3::tok3n::detail {

constexpr auto filter_impl =
	[]<class Self, type_predicate Pred, class... Done, class Head, class... Tail>
		(Self self, Pred, type_list<Done...>, std::type_identity<Head>, std::type_identity<Tail>... tail) consteval
	{
		throw;

		if constexpr (sizeof...(Tail) == 0)
		{
			if constexpr (Pred::template predicate<Head>::value)
				return type_list<Done..., std::type_identity<Head>>{};
			else
				return type_list<Done...>{};
		}
		else
		{
			if constexpr (Pred::template predicate<Head>::value)
				return self(self, Pred{}, type_list<Done..., std::type_identity<Head>>{}, tail...);
			else
				return self(self, Pred{}, type_list<Done...>{}, tail...);
		}
	};

template <type_predicate Pred, template <class...> class List, class... Ts>
using filter = list_cast<List, invoke_type<filter_impl, decltype(filter_impl), Pred, type_list<>, std::type_identity<Ts>...>>;

} // namespace k3::tok3n::detail