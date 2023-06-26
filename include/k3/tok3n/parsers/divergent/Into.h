#pragma once
#include <k3/tok3n/parsers/divergent/fwd.h>

namespace k3::tok3n {

template <Parser P, class T>
requires IntoConstructible<P, T>
struct Into
{
	using result_type = T;

	static constexpr ParserType type = IntoType;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, result_type(std::move(*result)), result.remaining()};
		else
			return { failure, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
