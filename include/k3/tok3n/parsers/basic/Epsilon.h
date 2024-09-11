#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>

namespace k3::tok3n {

template <class ValueType>
struct Epsilon
{
	using value_type = ValueType;
	
	template <detail::equality_comparable_with<value_type> V>
	using result_for = detail::front<void, V>;

	static constexpr detail::parser_family family = detail::epsilon_family;

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;
        return Result<void, V>{ success, input };
	}

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;
        return Result<void, V>{ success, input };
	}
};

} // namespace k3::tok3n
