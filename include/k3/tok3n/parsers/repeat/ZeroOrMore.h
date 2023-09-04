#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P>
requires ZeroOrMoreConstructible<P>
struct ZeroOrMore
{
	using result_type = std::vector<typename P::result_type>;

	static constexpr ParserType type = ZeroOrMoreType;

	static constexpr Result<result_type> parse(Input<char> input)
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
	
	static constexpr Result<void> lookahead(Input<char> input)
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

} // namespace k3::tok3n
