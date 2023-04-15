#pragma once
#include <k3/tok3n/namespace.h>
#include <concepts>
#include <type_traits>

TOK3N_BEGIN_NAMESPACE(meta)

template <class Pred>
concept type_predicate =
	requires { typename Pred::template predicate<void>; } and
	std::same_as<const bool, decltype(Pred::template predicate<void>::value)> and
	requires { std::bool_constant<(Pred::template predicate<void>::value, true)>{}; };

TOK3N_END_NAMESPACE(meta)
