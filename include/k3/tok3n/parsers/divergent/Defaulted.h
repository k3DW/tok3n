#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <Parser P, class T>
requires DefaultedConstructible<P, T>
struct Defaulted
{
	using value_type = typename P::value_type;

	template <EqualityComparableWith<value_type> V>
	using result_for = T;

	static constexpr ParserFamily family = DefaultedFamily;

	static constexpr Result<result_for<value_type>, value_type> parse(Input<value_type> input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, T{}, result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
