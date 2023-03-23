#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/types/Result.h"

TOK3N_BEGIN_NAMESPACE()

template <Parser P, auto function>
requires detail::ApplyTransform_able<P, function>
struct ApplyTransform
{
	using result_type = detail::ApplyTransform_result<P, function>;

	static constexpr ParserType type = ParserType::ApplyTransform;

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

TOK3N_END_NAMESPACE()
