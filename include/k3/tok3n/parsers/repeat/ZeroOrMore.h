#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <detail::parser P>
struct ZeroOrMore
{
	using value_type = typename P::value_type;

	template <detail::equality_comparable_with<value_type> V>
	using result_for = std::conditional_t<
		std::same_as<void, typename P::template result_for<V>>,
		void,
		std::vector<typename P::template result_for<V>>
	>;

	static constexpr detail::parser_family family = detail::zero_or_more_family;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		detail::ResultBuilder<result_for<V>> builder;

		while (true)
		{
			auto result = P::parse(input);
			input = result.remaining();
			if (not result.has_value())
				break;
			builder.insert_back(std::move(result));
		}

		return std::move(builder).success(input);
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		while (true)
		{
			auto result = P::lookahead(input);
			input = result.remaining();
			if (not result.has_value())
				break;
		}

		return Result<void, V>{ success, input };
	}
};

} // namespace k3::tok3n
