#pragma once
#include <tok3n/meta/type_predicate.h>

TOK3N_BEGIN_NAMESPACE(meta)

template <class T>
struct is_not_type
{
	template <class U>
	using predicate = std::bool_constant<not std::same_as<T, U>>;
};

TOK3N_END_NAMESPACE(meta)
