#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"
#include <vector>

namespace k3::parser
{

template <Parser P>
struct ZeroOrMore
{
	using result_type = std::vector<typename P::result_type>;

	static constexpr Result<result_type> parse(Input input)
	{
		const Input original_input = input;

		result_type results;
		while (true)
		{
			auto result = P::parse(input);
			if (result.has_value())
			{
				input = result.remaining();
				results.emplace_back(std::move(result.value()));
				continue;
			}
			else
				break;
		}

		return { success, std::move(results), input };
	}
};

}
