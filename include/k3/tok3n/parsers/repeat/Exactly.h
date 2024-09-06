#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P, IsConst<std::size_t> N>
requires (N::value != 0)
struct Exactly
{
	using value_type = typename P::value_type;

	template <EqualityComparableWith<value_type> V>
	using result_for = std::conditional_t<
		std::same_as<void, typename P::template result_for<V>>,
		void,
		std::array<typename P::template result_for<V>, N::value>
	>;

	static constexpr ParserFamily family = ExactlyFamily;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		const Input original_input = input;
		detail::ResultBuilder<result_for<V>> builder;

		for (std::size_t i = 0; i < N::value; i++)
		{
			auto result = P::parse(input);
			if (not result.has_value())
				return Result<result_for<V>, V>{ failure, original_input };

			input = result.remaining();
			builder.array_assign(i, std::move(result));
		}

		return std::move(builder).success(input);
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
			if (not result.has_value())
				return Result<void, V>{ failure, original_input };
			
			input = result.remaining();
		}

		return Result<void, V>{ success, input };
	}
};

} // namespace k3::tok3n
