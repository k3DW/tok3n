#pragma once
#include <k3/tok3n/detail/parsers/basic_base.h>
#include <k3/tok3n/detail/parsers/join.h>
#include <k3/tok3n/detail/parsers/exactly.h>

namespace k3::tok3n::detail {

template <template <static_array> class Basic, static_array arr, integral_constant_of<std::size_t> N>
struct join_parser<exactly_parser<Basic<arr>, N>>
{
	using value_type = typename Basic<arr>::value_type;
	
	template <equality_comparable_with<value_type> V>
	using result_for = output_span<V>;

	static constexpr parser_family family = join_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		using Traits = impl::basic_parser_traits<Basic<arr>>;

		const input_span original_input = input;
		output_span<V> res = { input.data(), 0 };

		for (std::size_t i = 0; i < N::value; i++)
		{
			if (Traits::failure_condition(input))
				return result<result_for<V>, V>{ failure_tag, original_input };
			res = { res.data(), res.size() + Traits::length };
			input = input.subspan(Traits::length);
		}

		return result<result_for<V>, V>{ success_tag, res, input };
	}
	
	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		using Traits = impl::basic_parser_traits<Basic<arr>>;

		const input_span original_input = input;

		for (std::size_t i = 0; i < N::value; i++)
		{
			if (Traits::failure_condition(input))
				return result<void, V>{ failure_tag, original_input };
			input = input.subspan(Traits::length);
		}

		return result<void, V>{ success_tag, input };
	}
};

} // namespace k3::tok3n::detail
