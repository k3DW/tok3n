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

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		detail::result_builder<result_for<V>> builder;

		while (true)
		{
			auto res = P::parse(input);
			input = res.remaining();
			if (not res.has_value())
				break;
			builder.insert_back(std::move(res));
		}

		return std::move(builder).build(input);
	}

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		while (true)
		{
			auto res = P::lookahead(input);
			input = res.remaining();
			if (not res.has_value())
				break;
		}

		return detail::result<void, V>{ detail::success_tag, input };
	}
};

} // namespace k3::tok3n
