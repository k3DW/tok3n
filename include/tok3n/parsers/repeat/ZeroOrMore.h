#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/types/Result.h"

TOK3N_BEGIN_NAMESPACE()

template <Parser P>
requires detail::ZeroOrMore_able<P>
struct ZeroOrMore
{
	using result_type = std::vector<typename P::result_type>;

	static constexpr ParserType type = ParserType::ZeroOrMore;

	static constexpr Result<result_type> parse(Input input)
	{
		const Input original_input = input;
		result_type results;

		while (true)
		{
			auto result = P::parse(input);
			if (result.has_value())
			{
				input = result.remaining();
				results.emplace_back(std::move(*result));
			}
			else
				break;
		}

		return { success, std::move(results), input };
	}
	
	static constexpr Result<void> lookahead(Input input)
	{
		Result<void> result;

		do
		{
			result = P::lookahead(input);
			input = result.remaining();
		} while (result.has_value());

		return { success, input };
	}
};

TOK3N_END_NAMESPACE()
