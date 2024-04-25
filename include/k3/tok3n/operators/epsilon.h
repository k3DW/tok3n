#pragma once
#include <k3/tok3n/parsers/basic/Epsilon.h>
#include <k3/tok3n/operators/choice.h>

namespace k3::tok3n {

struct EpsilonOperator
{
	template <class V>
	static constexpr Epsilon<V> of = {};
};

inline constexpr EpsilonOperator eps = {};

template <Parser P>
constexpr auto operator|(P, EpsilonOperator)
{
	return ::k3::tok3n::operator|(P{}, Epsilon<typename P::value_type>{});
}

template <Parser P>
constexpr auto operator|(EpsilonOperator, P) = delete;

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::eps;

} // namespace k3::tok3n::operators
