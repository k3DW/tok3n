#pragma once
#include <k3/tok3n/parsers/divergent/fwd.h>

namespace k3::tok3n {

template <Parser P, auto function>
requires ApplyTransformConstructible<P, function>
struct ApplyTransform
{
	using result_type = decltype(std::apply(function, std::declval<typename P::result_type>()));;

	static constexpr ParserType type = ApplyTransformType;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::apply(function, std::move(*result)), result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

} // namespace k3::tok3n
