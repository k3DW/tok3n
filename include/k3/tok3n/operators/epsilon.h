#pragma once
#include <k3/tok3n/detail/operators/choice.h>
#include <k3/tok3n/parsers/basic/Epsilon.h>

namespace k3::tok3n {

struct EpsilonOperator
{
	template <class V>
	static constexpr Epsilon<V> of = {};
};

inline constexpr EpsilonOperator eps = {};

template <detail::parser P>
constexpr auto operator|(P, EpsilonOperator)
{
	return ::k3::tok3n::detail::operator|(P{}, Epsilon<typename P::value_type>{});
}

template <detail::parser P>
constexpr auto operator|(EpsilonOperator, P) = delete;

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::eps;

} // namespace k3::tok3n::operators
