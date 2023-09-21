#pragma once
#include <k3/tok3n/parsers/repeat/_fwd.h>

namespace k3::tok3n {

template <Parser P>
requires MaybeConstructible<P>
struct Maybe
{
	using result_type = std::optional<typename P::result_type>;

	static constexpr ParserFamily type = MaybeType;

	static constexpr Result<result_type, char> parse(Input<char> input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::move(*result), result.remaining() };
		else
			return { success, result_type{ std::nullopt }, input };
	}

	static constexpr Result<void, char> lookahead(Input<char> input)
	{
		auto result = P::lookahead(input);
		if (result.has_value())
			return { success, result.remaining() };
		else
			return { success, input };
	}
};

} // namespace k3::tok3n
