#pragma once
#include "util/static_string.h"
#include "parsers/_decl.h"
#include "parsers/Result.h"
#include "parsers/NewResult.h"

namespace k3::parser
{

template <static_string str>
requires (str.unique_and_sorted()) && (str.ascii())
struct OneChar
{
	static constexpr Result parse(Input input)
	{
		if (input.empty() || not str.contains(input.front()))
			return Result::failure(input);
		else
		{
			const auto begin = input.begin();
			const auto end = input.end();
			return Result::success({ begin, begin + 1 }, { begin + 1, end });
		}
	}
};

template <static_string str>
requires (str.unique_and_sorted()) && (str.ascii())
struct NewOneChar
{
	using result_type = std::string_view;

	static constexpr NewResult<result_type> parse(Input input)
	{
		if (input.empty() || not str.contains(input.front()))
			return { failure, input };
		else
		{
			const auto begin = input.begin();
			return { success, { begin, begin + 1 }, { begin + 1, input.end() } };
		}
	}
};

}