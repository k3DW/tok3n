#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <Parser P, IsConst FunctionValue>
requires ApplyTransformConstructible<P, FunctionValue>
struct ApplyTransform
{
	using result_type = decltype(std::apply(FunctionValue::value, std::declval<typename P::result_type>()));;

	static constexpr ParserFamily type = ApplyTransformFamily;

	static constexpr Result<result_type, char> parse(Input<char> input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::apply(FunctionValue::value, std::move(*result)), result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void, char> lookahead(Input<char> input)
	{
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
