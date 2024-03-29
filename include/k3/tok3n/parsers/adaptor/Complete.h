#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n {

template <Parser P>
struct Complete
{
	using value_type = typename P::value_type;
	using result_type = typename P::result_type;

	static constexpr ParserFamily family = CompleteFamily;

	static constexpr Result<result_type, value_type> parse(Input<value_type> input)
	{
		return parse<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<result_type, V> parse(Input<V> input)
	{
		auto result = P::parse(input);
		if (not result.has_value() or result.remaining() != Input<V>{})
			return { failure, input };
		else
			return result;
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		return lookahead<value_type>(input);
	}

	template <std::convertible_to<value_type> V>
	static constexpr Result<void, V> lookahead(Input<V> input)
	{
		auto result = P::lookahead(input);
		if (not result.has_value() or result.remaining() != Input<V>{})
			return { failure, input };
		else
			return result;
	}
};

} // namespace k3::tok3n
