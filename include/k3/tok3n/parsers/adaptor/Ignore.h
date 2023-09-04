#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n {

template <Parser P>
struct Ignore
{
	using result_type = void;

	static constexpr ParserType type = IgnoreType;

	static constexpr Result<result_type, char> parse(Input<char> input)
	{
		return P::lookahead(input);
	}

	static constexpr Result<void, char> lookahead(Input<char> input)
	{
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
