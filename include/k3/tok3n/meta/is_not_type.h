#pragma once
#include <k3/tok3n/meta/type_predicate.h>

namespace k3::tok3n::meta {

template <class T>
struct is_not_type
{
	template <class U>
	using predicate = std::bool_constant<not std::same_as<T, U>>;
};

} // namespace k3::tok3n::meta
