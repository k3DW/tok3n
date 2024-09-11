#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <detail::parser P>
struct OneOrMore
{
	using value_type = typename P::value_type;

	template <detail::equality_comparable_with<value_type> V>
	using result_for = std::conditional_t<
		std::same_as<void, typename P::template result_for<V>>,
		void,
		std::vector<typename P::template result_for<V>>
	>;

	static constexpr detail::parser_family family = detail::one_or_more_family;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		detail::ResultBuilder<result_for<V>> builder;
		bool successful = false;

		while (true)
		{
			auto result = P::parse(input);
			input = result.remaining();
			successful |= result.has_value();
			if (not result.has_value())
				break;
			builder.insert_back(std::move(result));
		}

		if (successful)
			return std::move(builder).success(input);
		else
			return Result<result_for<V>, V>{ failure, input };
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		bool successful = false;

		while (true)
		{
			auto result = P::lookahead(input);
			input = result.remaining();
			successful |= result.has_value();
			if (not result.has_value())
				break;
		}

		if (successful)
			return Result<void, V>{ success, input };
		else
			return Result<void, V>{ failure, input };
	}
};

} // namespace k3::tok3n
