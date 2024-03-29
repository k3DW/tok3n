#pragma once
#include <k3/tok3n/detail/invoke_type.h>
#include <k3/tok3n/detail/type_predicate.h>

namespace k3::tok3n::detail {

inline constexpr auto filtered_sequence_impl =
	[]<class Self, type_predicate Pred, std::size_t Next, std::size_t... Is, class Head, class... Tail>
		(Self self, Pred, std::integral_constant<std::size_t, Next>, std::index_sequence<Is...>, std::type_identity<Head>, std::type_identity<Tail>... tail) consteval
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
				return self(self, Pred{}, std::integral_constant<std::size_t, Next + 1>{}, std::index_sequence<Is..., Next>{}, tail...);
			else
				return self(self, Pred{}, std::integral_constant<std::size_t, Next>{},     std::index_sequence<Is..., -1>{},   tail...);
		}
	};

template <type_predicate Pred, class... Ts>
using filtered_sequence = invoke_type<filtered_sequence_impl, decltype(filtered_sequence_impl), Pred, std::integral_constant<std::size_t, 0>, std::index_sequence<>, std::type_identity<Ts>...>;

} // namespace k3::tok3n::detail
