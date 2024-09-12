#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <vector>

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

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		detail::result_builder<result_for<V>> builder;
		bool successful = false;

		while (true)
		{
			auto res = P::parse(input);
			input = res.remaining();
			successful |= res.has_value();
			if (not res.has_value())
				break;
			builder.insert_back(std::move(res));
		}

		if (successful)
			return std::move(builder).build(input);
		else
			return detail::result<result_for<V>, V>{ detail::failure_tag, input };
	}

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		bool successful = false;

		while (true)
		{
			auto res = P::lookahead(input);
			input = res.remaining();
			successful |= res.has_value();
			if (not res.has_value())
				break;
		}

		if (successful)
			return detail::result<void, V>{ detail::success_tag, input };
		else
			return detail::result<void, V>{ detail::failure_tag, input };
	}
};

} // namespace k3::tok3n
