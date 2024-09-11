#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <class ValueType>
struct BasicTraits<Anything<ValueType>>
{
	using value_type = ValueType;

	static constexpr std::size_t length = 1;

	template <detail::equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(Input<V> input)
	{
		return input.empty();
	}
};

template <class ValueType>
struct Anything : BasicBase<Anything<ValueType>>
{
	static constexpr detail::parser_family family = detail::anything_family;
};

} // namespace k3::tok3n
