#pragma once
#include <k3/tok3n/parsers/basic/_fwd.h>
#include <k3/tok3n/parsers/basic/BasicBase.h>
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <template <StaticArray> class Basic, StaticArray arr, detail::integral_constant_of<std::size_t> N>
struct Join<Exactly<Basic<arr>, N>>
{
	using value_type = typename Basic<arr>::value_type;
	
	template <detail::equality_comparable_with<value_type> V>
	using result_for = detail::output_span<V>;

	static constexpr detail::parser_family family = detail::join_family;

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		using Traits = BasicTraits<Basic<arr>>;

		const detail::input_span original_input = input;
		detail::output_span<V> result = { input.data(), 0 };

		for (std::size_t i = 0; i < N::value; i++)
		{
			if (Traits::failure_condition(input))
				return Result<result_for<V>, V>{ failure, original_input };
			result = { result.data(), result.size() + Traits::length };
			input = input.subspan(Traits::length);
		}

		return Result<result_for<V>, V>{ success, result, input };
	}
	
	template <detail::input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		using Traits = BasicTraits<Basic<arr>>;

		const detail::input_span original_input = input;

		for (std::size_t i = 0; i < N::value; i++)
		{
			if (Traits::failure_condition(input))
				return Result<void, V>{ failure, original_input };
			input = input.subspan(Traits::length);
		}

		return Result<void, V>{ success, input };
	}
};

} // namespace k3::tok3n
