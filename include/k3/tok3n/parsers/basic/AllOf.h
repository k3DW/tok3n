#pragma once
#include <k3/tok3n/parsers/basic/BasicBase.h>

namespace k3::tok3n {

template <detail::static_array arr>
struct AllOf : BasicBase<AllOf<arr>>
{
	static constexpr detail::parser_family family = detail::all_of_family;
};

template <detail::static_array arr>
struct BasicTraits<AllOf<arr>>
{
	using value_type = typename decltype(arr)::value_type;

	static constexpr std::size_t length = arr.size();

	template <detail::equality_comparable_with<value_type> V>
	static constexpr bool failure_condition(detail::input_span<V> input)
	{
		return (input.size() < length) || (detail::input_span<value_type>(arr.span()) != detail::input_span<V>(input.first(length)));
	}
};

} // namespace k3::tok3n
