#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <Parser P, class T>
requires ApplyIntoConstructible<P, T>
struct ApplyInto
{
	using result_type = T;

	static constexpr ParserType type = ApplyIntoType;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::make_from_tuple<result_type>(std::move(*result)), result.remaining()};
		else
			return { failure, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
