#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <Parser P, IsConst Value>
struct Constant
{
	using result_type = typename Value::value_type;

	static constexpr ParserType type = ConstantType;

	static constexpr Result<result_type, char> parse(Input<char> input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, Value::value, result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void, char> lookahead(Input<char> input)
	{
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
