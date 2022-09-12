#pragma once
#include "util/static_string.h"
#include "parsers/_decl.h"
#include "parsers/Result.h"
#include "parsers/NewResult.h"

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

template <static_string str>
requires (str.ascii()) && (str.size() > 0)
struct NewLiteral
{
	static constexpr NewResult<std::string_view> parse(Input input)
	{
		if (input.empty() || not input.starts_with({ str.begin(), str.end() }))
			return { failure, input };
		else
		{
			const auto begin = input.begin();
			const auto end = input.end();
			return { success, { begin, begin + str.size() }, { begin + str.size(), end } };
		}
	}
};

}
