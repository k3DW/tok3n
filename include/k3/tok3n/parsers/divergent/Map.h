#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <detail::parser P, detail::is_integral_constant FunctionValue>
struct Map
{
	using value_type = typename P::value_type;

	template <detail::equality_comparable_with<value_type> V>
	using result_for = typename std::conditional_t<
		std::same_as<void, typename P::template result_for<V>>,
		std::invoke_result<typename FunctionValue::value_type>,
		std::invoke_result<typename FunctionValue::value_type, typename P::template result_for<V>>
	>::type;

	static constexpr detail::parser_family family = detail::map_family;

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		detail::input_span input{ std::forward<R>(r) };
		using V = detail::input_value_t<R>;

		using before_type = typename P::template result_for<V>;
		using after_type = result_for<V>;

		auto res = P::parse(input);
		if (not res.has_value())
			return detail::result<after_type, V>{ detail::failure_tag, input };

		if constexpr (std::same_as<void, before_type>)
		{
			if constexpr (std::same_as<void, after_type>)
			{
				std::invoke(FunctionValue::value);
				return detail::result<after_type, V>{ detail::success_tag, res.remaining() };
			}
			else
				return detail::result<after_type, V>{ detail::success_tag, std::invoke(FunctionValue::value), res.remaining() };
		}
		else
		{
			if constexpr (std::same_as<void, after_type>)
			{
				std::invoke(FunctionValue::value, std::move(*res));
				return detail::result<after_type, V>{ detail::success_tag, res.remaining() };
			}
			else
				return detail::result<after_type, V>{ detail::success_tag, std::invoke(FunctionValue::value, std::move(*res)), res.remaining() };
		}
	}

	template <detail::input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return P::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n
