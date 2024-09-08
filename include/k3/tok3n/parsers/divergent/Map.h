#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <Parser P, detail::is_integral_constant FunctionValue>
struct Map
{
	using value_type = typename P::value_type;

	template <detail::equality_comparable_with<value_type> V>
	using result_for = typename std::conditional_t<
		std::same_as<void, typename P::template result_for<V>>,
		std::invoke_result<typename FunctionValue::value_type>,
		std::invoke_result<typename FunctionValue::value_type, typename P::template result_for<V>>
	>::type;

	static constexpr ParserFamily family = MapFamily;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		using before_type = typename P::template result_for<V>;
		using after_type = result_for<V>;

		auto result = P::parse(input);
		if (not result.has_value())
			return Result<after_type, V>{ failure, input };

		if constexpr (std::same_as<void, before_type>)
		{
			if constexpr (std::same_as<void, after_type>)
			{
				std::invoke(FunctionValue::value);
				return Result<after_type, V>{ success, result.remaining() };
			}
			else
				return Result<after_type, V>{ success, std::invoke(FunctionValue::value), result.remaining() };
		}
		else
		{
			if constexpr (std::same_as<void, after_type>)
			{
				std::invoke(FunctionValue::value, std::move(*result));
				return Result<after_type, V>{ success, result.remaining() };
			}
			else
				return Result<after_type, V>{ success, std::invoke(FunctionValue::value, std::move(*result)), result.remaining() };
		}
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return P::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n
