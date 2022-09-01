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
	static constexpr Result parse(Input input)
	{
		if (input.empty() || not input.starts_with({ str.begin(), str.end() }))
			return Result::failure(input);
		else
		{
			const auto begin = input.begin();
			const auto end = input.end();
			return Result::success({ begin, begin + str.size() }, { begin + str.size(), end });
		}
	}
};

}
