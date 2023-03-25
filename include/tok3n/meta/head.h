#pragma once
#include <tok3n/meta/invoke_type.h>

TOK3N_BEGIN_NAMESPACE(meta)

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

TOK3N_END_NAMESPACE(meta)
