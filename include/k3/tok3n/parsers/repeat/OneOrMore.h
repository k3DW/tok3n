#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P>
struct OneOrMore
{
	using value_type = typename P::value_type;

	template <EqualityComparableWith<value_type> V>
	using result_for = std::vector<typename P::template result_for<V>>;

	static constexpr ParserFamily family = OneOrMoreFamily;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		static_assert(not std::same_as<typename P::template result_for<value_type>, void>,
			"OneOrMore's child parser's result for the given value cannot be void.");

		const Input original_input = input;
		result_for<value_type> results;

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
		static_assert(not std::same_as<typename P::template result_for<value_type>, void>,
			"OneOrMore's child parser's result for the given value cannot be void.");

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
