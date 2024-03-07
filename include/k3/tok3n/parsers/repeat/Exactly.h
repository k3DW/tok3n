#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P, IsConst<std::size_t> N>
requires ExactlyConstructible<P, N>
struct Exactly
{
	using value_type = typename P::value_type;
	using result_type = std::array<typename P::result_type, N::value>;

	static constexpr ParserFamily family = ExactlyFamily;

	static constexpr Result<result_type, value_type> parse(Input<value_type> input)
	{
		return parse<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<result_type, V> parse(Input<V> input)
	{
		const Input original_input = input;
		result_type results;

		for (std::size_t i = 0; i < N::value; i++)
		{
			auto result = P::parse(input);
			if (result.has_value())
			{
				input = result.remaining();
				results[i] = std::move(*result);
			}
			else
				return { failure, original_input };
		}

		return { success, std::move(results), input };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		return lookahead<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<void, V> lookahead(Input<V> input)
	{
		const Input original_input = input;

		for (std::size_t i = 0; i < N::value; i++)
		{
			auto result = P::lookahead(input);
			if (result.has_value())
				input = result.remaining();
			else
				return { failure, original_input };
		}

		return { success, input };
	}
};

} // namespace k3::tok3n
