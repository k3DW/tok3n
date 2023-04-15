#pragma once
#include <k3/tok3n/meta/invoke_type.h>
#include <k3/tok3n/meta/type_predicate.h>
#include <k3/tok3n/meta/list_cast.h>

#include <k3/tok3n/meta/is_not_type.h>
#include <tuple>

TOK3N_BEGIN_NAMESPACE(meta)

namespace detail
{

	constexpr auto filter =
		[]<class Self, type_predicate Pred, class... Done, class Head, class... Tail>
			(this Self self, Pred, type_list<Done...>, std::type_identity<Head>, std::type_identity<Tail>... tail) consteval
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
					return self(Pred{}, type_list<Done..., std::type_identity<Head>>{}, tail...);
				else
					return self(Pred{}, type_list<Done...>{}, tail...);
			}
		};

}

template <type_predicate Pred, template <class...> class List, class... Ts>
using filter = list_cast<List, invoke_type<detail::filter, Pred, type_list<>, std::type_identity<Ts>...>>;

TOK3N_END_NAMESPACE(meta)
