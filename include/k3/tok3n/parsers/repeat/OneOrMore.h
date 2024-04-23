#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P>
struct OneOrMore
{
	using value_type = typename P::value_type;

	template <InputConstructibleFor<value_type> R, class V = typename decltype(Input{ std::declval<R>() })::value_type>
	static constexpr bool parsable_range = not std::same_as<typename P::template result_for<V>, void>;

	template <EqualityComparableWith<value_type> V>
	using result_for = std::vector<typename P::template result_for<V>>;

	static constexpr ParserFamily family = OneOrMoreFamily;

	template <InputConstructibleFor<value_type> R>
	requires parsable_range<R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		const Input original_input = input;
		result_for<V> results;

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
			return Result<result_for<V>, V>{ success, std::move(results), input };
		else
			return Result<result_for<V>, V>{ failure, original_input };
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		Result<void, V> result;
		bool successful = false;
		
		do
		{
			result = P::lookahead(input);
			input = result.remaining();
			successful |= result.has_value();
		} while (result.has_value());

		if (successful)
			return Result<void, V>{ success, input };
		else
			return Result<void, V>{ failure, input };
	}
};

} // namespace k3::tok3n
