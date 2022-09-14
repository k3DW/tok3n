#pragma once
#include "util/static_string.h"
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::parser
{

template <static_string str>
requires (str.ascii()) && (str.size() > 0)
struct Literal
{
	using result_type = std::string_view;

	static constexpr Result<result_type> parse(Input input)
	{
		if (input.empty() || not input.starts_with({ str.begin(), str.end() }))
			return { failure, input };
		else
		{
			const auto begin = input.begin();
			return { success, { begin, begin + str.size() }, { begin + str.size(), input.end() } };
		}
	}
};

}
