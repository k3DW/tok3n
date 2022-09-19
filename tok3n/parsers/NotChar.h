#pragma once
#include "util/static_string.h"
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::parser
{

template <static_string str>
requires (str.unique_and_sorted()) && (str.ascii()) && (str.size() > 0)
struct NotChar
{
	using result_type = std::string_view;

	static constexpr Result<result_type> parse(Input input)
	{
		if (input.empty() || str.contains(input.front()))
			return { failure, input };
		else
		{
			const auto begin = input.begin();
			return { success, { begin, begin + 1 }, { begin + 1, input.end() } };
		}
	}
};

}
