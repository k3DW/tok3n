#pragma once
#include <concepts>
#include <type_traits>

namespace k3::tok3n::detail {

template <class T>
struct is_not_type
{
	template <class U>
	using predicate = std::bool_constant<not std::same_as<T, U>>;
};

} // namespace k3::tok3n::detail
