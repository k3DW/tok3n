#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P, detail::is_integral_constant<std::size_t> N>
requires ExactlyConstructible<P, N>
struct Exactly
{
	using result_type = std::array<typename P::result_type, N::value>;

	static constexpr ParserType type = ExactlyType;

	static constexpr Result<result_type> parse(Input input)
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

	static constexpr Result<void> lookahead(Input input)
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
