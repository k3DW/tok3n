#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

namespace k3::tok3n
{

template <Parser P>
struct ZeroOrOne
{
	using result_type = std::optional<typename P::result_type>;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
			return { success, result_type{ std::move(result.value()) }, result.remaining() };
		else
			return { success, result_type{ std::nullopt }, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		auto result = P::lookahead(input);
		if (result)
			return { success, result.remaining() };
		else
			return { success, input };
	}
};

}
