#pragma once
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>

namespace k3::tok3n::detail {

namespace impl {

template <class P>
struct basic_parser_traits
{
	// using value_type;
	// static constexpr std::size_t length;
	// static constexpr bool failure_condition(input_span<value_type>);
};

template <class P>
struct basic_parser_base
{
	using value_type = typename basic_parser_traits<P>::value_type;
	
	template <equality_comparable_with<value_type> V>
    using result_for = output_span<V>;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		using Traits = basic_parser_traits<P>;
		if (Traits::failure_condition(input))
			return result<result_for<V>, V>{ failure_tag, input };
		else
			return result<result_for<V>, V>{ success_tag, { input.data(), Traits::length }, { input.data() + Traits::length, input.size() - Traits::length } };
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		using Traits = basic_parser_traits<P>;
		if (Traits::failure_condition(input))
			return result<void, V>{ failure_tag, input };
		else
			return result<void, V>{ success_tag, { input.data() + Traits::length, input.size() - Traits::length } };
	}
};

} // namespace impl

} // namespace k3::tok3n::detail
