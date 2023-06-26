#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <Parser P, auto value>
struct Constant
{
	using result_type = decltype(value);

	static constexpr ParserType type = ConstantType;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, value, result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
