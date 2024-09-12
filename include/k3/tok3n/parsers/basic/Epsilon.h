#pragma once
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>

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
        return detail::result<void, V>{ detail::success_tag, input };
	}

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;
        return detail::result<void, V>{ detail::success_tag, input };
	}
};

} // namespace k3::tok3n
