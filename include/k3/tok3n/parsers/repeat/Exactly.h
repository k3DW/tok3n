#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P, IsConst<std::size_t> N>
requires (N::value != 0)
struct Exactly
{
	using value_type = typename P::value_type;

	template <InputConstructibleFor<value_type> R, class V = InputValueType<R>>
	static constexpr bool parsable_range = not std::same_as<typename P::template result_for<V>, void>;

	template <EqualityComparableWith<value_type> V>
	using result_for = std::array<typename P::template result_for<V>, N::value>;

	static constexpr ParserFamily family = ExactlyFamily;

	template <InputConstructibleFor<value_type> R>
	requires parsable_range<R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		const Input original_input = input;
		result_for<V> results;

		for (std::size_t i = 0; i < N::value; i++)
		{
			auto result = P::parse(input);
			if (result.has_value())
			{
				input = result.remaining();
				results[i] = std::move(*result);
			}
			else
				return Result<result_for<V>, V>{ failure, original_input };
		}

		return Result<result_for<V>, V>{ success, std::move(results), input };
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		const Input original_input = input;

		for (std::size_t i = 0; i < N::value; i++)
		{
			auto result = P::lookahead(input);
			if (result.has_value())
				input = result.remaining();
			else
				return Result<void, V>{ failure, original_input };
		}

		return Result<void, V>{ success, input };
	}
};

} // namespace k3::tok3n
