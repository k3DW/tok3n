#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n {

template <Parser P>
consteval auto Ignore_value_type_helper(P)
{
	// TODO: Remove this later, once I have non-char support across all parsers
	throw;

	if constexpr (requires { typename P::value_type; })
		return typename P::value_type{};
	else
		return char{};
}

template <Parser P>
struct Ignore
{
	using result_type = void;
	using value_type = decltype(Ignore_value_type_helper(P{}));

	static constexpr ParserFamily family = IgnoreFamily;

	static constexpr Result<result_type, value_type> parse(Input<value_type> input)
	{
		return P::lookahead(input);
	}

	static constexpr Result<void, value_type> lookahead(Input<value_type> input)
	{
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
