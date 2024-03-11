#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <Parser P, IsConst FunctionValue>
struct ApplyTransform
{
	using value_type = typename P::value_type;

	template <EqualityComparableWith<value_type> V>
	using result_for = decltype(std::apply(FunctionValue::value, std::declval<typename P::template result_for<V>>()));;

	static constexpr ParserFamily family = ApplyTransformFamily;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		static_assert(detail::has_tuple_size<typename P::template result_for<value_type>>,
			"ApplyTransform's child parser's result type for the given value must have tuple_size.");
		static_assert(requires { std::apply(FunctionValue::value, std::declval<typename P::template result_for<value_type>>()); },
			"ApplyTransform's function must be apply-able with its child parser's result for the given value type.");

		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::apply(FunctionValue::value, std::move(*result)), result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		static_assert(detail::has_tuple_size<typename P::template result_for<value_type>>,
			"ApplyTransform's child parser's result type for the given value must have tuple_size.");
		static_assert(requires { std::apply(FunctionValue::value, std::declval<typename P::template result_for<value_type>>()); },
			"ApplyTransform's function must be apply-able with its child parser's result for the given value type.");
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
