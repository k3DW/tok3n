#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::parser
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
};

}
