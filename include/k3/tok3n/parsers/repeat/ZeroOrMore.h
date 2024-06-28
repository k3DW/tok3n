#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P>
struct ZeroOrMore
{
	using value_type = typename P::value_type;

	template <InputConstructibleFor<value_type> R, class V = InputValueType<R>>
	static constexpr bool parsable_range = not std::same_as<typename P::template result_for<V>, void>;

	template <EqualityComparableWith<value_type> V>
	using result_for = std::vector<typename P::template result_for<V>>;

	static constexpr ParserFamily family = ZeroOrMoreFamily;

	template <InputConstructibleFor<value_type> R>
	requires parsable_range<R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

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

		return Result<result_for<V>, V>{ success, std::move(results), input };
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		Result<void, V> result;

		do
		{
			result = P::lookahead(input);
			input = result.remaining();
		} while (result.has_value());

		return Result<void, V>{ success, input };
	}
};

} // namespace k3::tok3n
