#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n {

template <Parser P>
struct Complete
{
	using result_type = typename P::result_type;

	static constexpr ParserType type = CompleteType;

	static constexpr Result<result_type> parse(Input<char> input)
	{
		auto result = P::parse(input);
		if (not result.has_value() or result.remaining() != "")
			return { failure, input };
		else
			return result;
	}

	static constexpr Result<void> lookahead(Input<char> input)
	{
		auto result = P::lookahead(input);
		if (not result.has_value() or result.remaining() != "")
			return { failure, input };
		else
			return result;
	}
};

} // namespace k3::tok3n
