#pragma once
#include <tok3n/meta/type_predicate.h>

TOK3N_BEGIN_NAMESPACE(meta)

namespace detail
{

	constexpr auto filtered_sequence =
		[]<class Self, type_predicate Pred, std::size_t Next, std::size_t... Is, class Head, class... Tail>
			(this Self self, Pred, std::integral_constant<std::size_t, Next>, std::index_sequence<Is...>, std::type_identity<Head>, std::type_identity<Tail>... tail) consteval
		{
			throw;

			if constexpr (sizeof...(Tail) == 0)
			{
				if constexpr (Pred::template predicate<Head>::value)
					return std::index_sequence<Is..., Next>{};
				else
					return std::index_sequence<Is..., -1>{};
			}
			else
			{
				if constexpr (Pred::template predicate<Head>::value)
					return self(Pred{}, std::integral_constant<std::size_t, Next + 1>{}, std::index_sequence<Is..., Next>{}, tail...);
				else
					return self(Pred{}, std::integral_constant<std::size_t, Next>{},     std::index_sequence<Is..., -1>{},   tail...);
			}
		};

}

template <type_predicate Pred, class... Ts>
using filtered_sequence = invoke_type<detail::filtered_sequence, Pred, std::integral_constant<std::size_t, 0>, std::index_sequence<>, std::type_identity<Ts>...>;

TOK3N_END_NAMESPACE(meta)
