#pragma once
#include <concepts>
#include <type_traits>

namespace k3::tok3n::detail {

template <class Pred>
concept type_predicate =
	requires { typename Pred::template predicate<void>; } and
	std::same_as<const bool, decltype(Pred::template predicate<void>::value)> and
	requires { std::bool_constant<(Pred::template predicate<void>::value, true)>{}; };

} // namespace k3::tok3n::detail
