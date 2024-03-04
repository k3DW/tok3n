#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P>
requires ZeroOrMoreConstructible<P>
struct ZeroOrMore
{
	using value_type = typename P::value_type;
	using result_type = std::vector<typename P::result_type>;

	static constexpr ParserFamily family = ZeroOrMoreFamily;

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

		return { success, std::move(results), input };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		Result<void, value_type> result;

		do
		{
			result = P::lookahead(input);
			input = result.remaining();
		} while (result.has_value());

		return { success, input };
	}
};

} // namespace k3::tok3n
