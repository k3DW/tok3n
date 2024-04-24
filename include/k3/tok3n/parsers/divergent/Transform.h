#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <Parser P, IsConst FunctionValue>
struct Transform
{
	using value_type = typename P::value_type;

	template <EqualityComparableWith<value_type> V>
	using result_for = decltype(std::invoke(FunctionValue::value, std::declval<typename P::template result_for<V>>()));

	static constexpr ParserFamily family = TransformFamily;

	template <InputConstructibleFor<value_type> R>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		auto result = P::parse(input);
		if (not result.has_value())
			return Result<result_for<V>, V>{ failure, input };

		if constexpr (std::same_as<result_for<V>, void>)
		{
			std::invoke(FunctionValue::value, std::move(*result));
			return Result<result_for<V>, V>{ success, result.remaining() };
		}
		else
			return Result<result_for<V>, V>{ success, std::invoke(FunctionValue::value, std::move(*result)), result.remaining() };
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return P::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n
