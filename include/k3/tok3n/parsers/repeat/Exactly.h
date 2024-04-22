#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P, IsConst<std::size_t> N>
requires (N::value != 0)
struct Exactly
{
	using value_type = typename P::value_type;

	template <EqualityComparableWith<value_type> V>
	using result_for = std::array<typename P::template result_for<V>, N::value>;

	static constexpr ParserFamily family = ExactlyFamily;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		static_assert(not std::same_as<typename P::template result_for<value_type>, void>,
			"Exactly's child parser's result for the given value cannot be void.");

		const Input original_input = input;
		result_for<value_type> results;

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
		static_assert(not std::same_as<typename P::template result_for<value_type>, void>,
			"Exactly's child parser's result for the given value cannot be void.");

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
