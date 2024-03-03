#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P>
requires OneOrMoreConstructible<P>
struct OneOrMore
{
	using value_type = typename P::value_type;
	using result_type = std::vector<typename P::result_type>;

	static constexpr ParserFamily family = OneOrMoreFamily;

	static constexpr Result<result_type, value_type> parse(Input<value_type> input)
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

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		Result<void, value_type> result;
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

} // namespace k3::tok3n
