#pragma once
#include <k3/tok3n/detail/operators/choice.h>
#include <k3/tok3n/parsers/basic/Epsilon.h>

namespace k3::tok3n::detail {

struct epsilon_operator
{
	template <class V>
	static constexpr Epsilon<V> of = {};
};

template <parser P>
constexpr auto operator|(P, epsilon_operator)
{
	return ::k3::tok3n::detail::operator|(P{}, Epsilon<typename P::value_type>{});
}

template <parser P>
constexpr auto operator|(epsilon_operator, P) = delete;

} // namespace k3::tok3n::detail
