#pragma once
#include <tok3n/meta/invoke_type.h>
#include <concepts>

TOK3N_BEGIN_NAMESPACE(meta)

namespace impl
{

	constexpr auto all_same =
		[]<class T, class... Ts>
			(T, Ts...) consteval
		-> std::bool_constant<(... && std::same_as<T, Ts>)>
		{
			throw;
		};

}

template <class... Ts>
concept all_same = invoke_type<impl::all_same, std::type_identity<Ts>...>::value;

TOK3N_END_NAMESPACE(meta)
