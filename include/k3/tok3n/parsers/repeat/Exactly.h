#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <array>

namespace k3::tok3n {

template <detail::parser P, detail::integral_constant_of<std::size_t> N>
requires (N::value != 0)
struct Exactly
{
	using value_type = typename P::value_type;

	template <detail::equality_comparable_with<value_type> V>
	using result_for = std::conditional_t<
		std::same_as<void, typename P::template result_for<V>>,
		void,
		std::array<typename P::template result_for<V>, N::value>
	>;

	static constexpr detail::parser_family family = detail::exactly_family;

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		const detail::input_span original_input = input;
		detail::result_builder<result_for<V>> builder;

		for (std::size_t i = 0; i < N::value; i++)
		{
			auto res = P::parse(input);
			if (not res.has_value())
				return detail::result<result_for<V>, V>{ detail::failure_tag, original_input };

			input = res.remaining();
			builder.array_assign(i, std::move(res));
		}

		return std::move(builder).build(input);
	}

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		const detail::input_span original_input = input;

		for (std::size_t i = 0; i < N::value; i++)
		{
			auto res = P::lookahead(input);
			if (not res.has_value())
				return detail::result<void, V>{ detail::failure_tag, original_input };
			
			input = res.remaining();
		}

		return detail::result<void, V>{ detail::success_tag, input };
	}
};

} // namespace k3::tok3n
