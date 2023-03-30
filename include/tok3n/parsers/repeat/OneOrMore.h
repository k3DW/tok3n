#pragma once
#include <tok3n/parsers/_constructible/repeat.h>
#include <tok3n/types.h>
#include <tok3n/concepts.h>

TOK3N_BEGIN_NAMESPACE()

template <Parser P>
requires constructible::OneOrMore<P>
struct OneOrMore
{
	using result_type = std::vector<typename P::result_type>;

	static constexpr ParserType type = OneOrMoreType;

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

		if (results.size() != 0)
			return { success, std::move(results), input };
		else
			return { failure, original_input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		Result<void> result;
		bool successful = false;
		
		do
		{
			result = P::lookahead(input);
			input = result.remaining();
			successful |= result.has_value();
		} while (result.has_value());

		if (successful)
			return { success, input };
		else
			return { failure, input };
	}
};

TOK3N_END_NAMESPACE()
