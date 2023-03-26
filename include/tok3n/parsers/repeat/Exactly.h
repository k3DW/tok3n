#pragma once
#include "tok3n/parsers/Details.h"
#include "tok3n/types.h"
#include "tok3n/concepts.h"

TOK3N_BEGIN_NAMESPACE()

template <Parser P, std::size_t N>
requires detail::Exactly_able<P, N>
struct Exactly
{
	using result_type = std::array<typename P::result_type, N>;

	static constexpr ParserType type = ExactlyType;

	static constexpr Result<result_type> parse(Input input)
	{
		const Input original_input = input;
		result_type results;

		for (std::size_t i = 0; i < N; i++)
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

		for (std::size_t i = 0; i < N; i++)
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

TOK3N_END_NAMESPACE()
