#pragma once
#include <k3/tok3n/meta/invoke_type.h>

namespace k3::tok3n::meta {

namespace detail
{

	constexpr auto head =
		[]<class T, class... Ts>
			(T, Ts...) consteval
		-> T
		{
			throw;
		};

}

template <class... Ts>
using head = typename invoke_type<detail::head, std::type_identity<Ts>...>::type;

} // namespace k3::tok3n::meta
