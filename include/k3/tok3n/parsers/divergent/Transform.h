#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <Parser P, IsConst FunctionValue>
requires TransformConstructible<P, FunctionValue>
struct Transform
{
	using result_type = decltype(std::invoke(FunctionValue::value, std::declval<typename P::result_type>()));

	static constexpr ParserType type = TransformType;

	static constexpr Result<result_type> parse(Input<char> input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::invoke(FunctionValue::value, std::move(*result)), result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void> lookahead(Input<char> input)
	{
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
