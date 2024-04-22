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

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		static_assert(requires { std::invoke(FunctionValue::value, std::declval<typename P::template result_for<value_type>>()); },
			"Transform's function must be callable with its child parser's result for the given value type.");

		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::invoke(FunctionValue::value, std::move(*result)), result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		static_assert(requires { std::invoke(FunctionValue::value, std::declval<typename P::template result_for<value_type>>()); },
			"Transform's function must be callable with its child parser's result for the given value type.");
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
