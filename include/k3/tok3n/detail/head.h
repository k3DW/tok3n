#pragma once
#include <k3/tok3n/detail/invoke_type.h>

namespace k3::tok3n::detail {

constexpr auto head_impl =
	[]<class T, class... Ts>
		(T, Ts...) consteval
	-> T
	{
		throw;
	};

template <class... Ts>
using head = typename invoke_type<head_impl, std::type_identity<Ts>...>::type;

} // namespace k3::tok3n::detail
