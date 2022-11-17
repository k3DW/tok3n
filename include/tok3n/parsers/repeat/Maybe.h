#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

TOK3N_BEGIN_NAMESPACE()

template <Parser P>
requires detail::Maybe_able<P>
struct Maybe
{
	using result_type = std::optional<typename P::result_type>;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, std::move(*result), result.remaining() };
		else
			return { success, result_type{ std::nullopt }, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		auto result = P::lookahead(input);
		if (result.has_value())
			return { success, result.remaining() };
		else
			return { success, input };
	}
};

TOK3N_END_NAMESPACE()
