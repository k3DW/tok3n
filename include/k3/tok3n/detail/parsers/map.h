#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>
#include <functional>

namespace k3::tok3n::detail {

template <parser P, is_integral_constant FunctionValue>
struct map_parser
{
	using value_type = typename P::value_type;

	template <equality_comparable_with<value_type> V>
	using result_for = typename std::conditional_t<
		std::same_as<void, typename P::template result_for<V>>,
		std::invoke_result<typename FunctionValue::value_type>,
		std::invoke_result<typename FunctionValue::value_type, typename P::template result_for<V>>
	>::type;

	static constexpr parser_family family = map_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		using before_type = typename P::template result_for<V>;
		using after_type = result_for<V>;

		auto res = P::parse(input);
		if (not res.has_value())
			return result<after_type, V>{ failure_tag, input };

		if constexpr (std::same_as<void, before_type>)
		{
			if constexpr (std::same_as<void, after_type>)
			{
				std::invoke(FunctionValue::value);
				return result<after_type, V>{ success_tag, res.remaining() };
			}
			else
				return result<after_type, V>{ success_tag, std::invoke(FunctionValue::value), res.remaining() };
		}
		else
		{
			if constexpr (std::same_as<void, after_type>)
			{
				std::invoke(FunctionValue::value, std::move(*res));
				return result<after_type, V>{ success_tag, res.remaining() };
			}
			else
				return result<after_type, V>{ success_tag, std::invoke(FunctionValue::value, std::move(*res)), res.remaining() };
		}
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return P::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n::detail
