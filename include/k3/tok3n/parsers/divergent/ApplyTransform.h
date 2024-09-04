#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>
#include <k3/tok3n/detail/apply.h>

namespace k3::tok3n {

template <Parser P, IsConst FunctionValue>
struct ApplyTransform
{
	using value_type = typename P::value_type;

	template <EqualityComparableWith<value_type> V>
	using result_for = decltype(detail::apply(FunctionValue::value, std::declval<typename P::template result_for<V>>()));

	static constexpr ParserFamily family = ApplyTransformFamily;

	template <InputConstructibleFor<value_type> R>
	requires requires { typename result_for<InputValueType<R>>; }
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = InputValueType<R>;

		auto result = P::parse(input);
		if (not result.has_value())
			return Result<result_for<V>, V>{ failure, input };
			
		if constexpr (std::same_as<result_for<V>, void>)
		{
			detail::apply(FunctionValue::value, std::move(*result));
			return Result<result_for<V>, V>{ success, result.remaining() };
		}
		else
			return Result<result_for<V>, V>{ success, detail::apply(FunctionValue::value, std::move(*result)), result.remaining() };
	}

	template <InputConstructibleFor<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		return P::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n
