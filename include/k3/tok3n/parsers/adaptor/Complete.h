#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n {

template <Parser P>
struct Complete
{
	using value_type = typename P::value_type;
	
	template <EqualityComparableWith<value_type> V>
	using result_for = typename P::template result_for<V>;

	static constexpr ParserFamily family = CompleteFamily;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		auto result = P::parse(input);
		if (not result.has_value() or result.remaining() != Input<value_type>{})
			return { failure, input };
		else
			return result;
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		auto result = P::lookahead(input);
		if (not result.has_value() or result.remaining() != Input<value_type>{})
			return { failure, input };
		else
			return result;
	}
};

} // namespace k3::tok3n
