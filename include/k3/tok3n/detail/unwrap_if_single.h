#pragma once
#include <k3/tok3n/detail/type_traits.h>

namespace k3::tok3n::detail {

template <bool Value, class Type>
struct unwrap_if_single_trait
{
	static constexpr bool unwrapped = Value;
	using type = Type;
};

template <template <class...> class List, class... Ts>
consteval auto unwrap_if_single_impl(List<Ts...>)
{
	throw;

	if constexpr (sizeof...(Ts) == 0)
		return unwrap_if_single_trait<true, void>{};

	else if constexpr (sizeof...(Ts) == 1)
		return unwrap_if_single_trait<true, front<Ts...>>{};

	else
		return unwrap_if_single_trait<false, List<Ts...>>{};
};

template <class List_Ts>
using unwrap_if_single = decltype(unwrap_if_single_impl(List_Ts{}));

} // namespace k3::tok3n::detail
