#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <Parser P, IsConst Value>
struct Constant
{
	using value_type = typename P::value_type;
	using result_type = typename Value::value_type;

	static constexpr ParserFamily family = ConstantFamily;

	static constexpr Result<result_type, value_type> parse(Input<value_type> input)
	{
		return parse<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<result_type, V> parse(Input<V> input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, Value::value, result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		return lookahead<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<void, V> lookahead(Input<V> input)
	{
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
