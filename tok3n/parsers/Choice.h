#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"
#include "parsers/NewResult.h"

namespace k3::parser
{

struct ChoiceExec
{
	Input input;
	Result& result_ref;

	template <Parser P>
	constexpr bool operator()(P) const
	{
		Result result = P::parse(input);
		if (result.has_value())
		{
			result_ref = std::move(result);
			return true;
		}
		else
			return false;
	}
};

template <Parser... Ps>
requires (sizeof...(Ps) >= 2)
struct Choice
{
	static constexpr Result parse(Input input)
	{
		Result result = Result::failure(input);
		const auto executor = ChoiceExec{ .input = input, .result_ref = result };
		(... || executor(Ps{}));

		return result;
	}
};

template <class result_type>
struct NewChoiceExec
{
	Input input;
	NewResult<result_type>& result_ref;

	template <Parser P>
	constexpr bool execute() const
	{
		NewResult<result_type> result = P::parse(input);
		if (result.has_value())
		{
			result_ref = std::move(result);
			return true;
		}
		else
			return false;
	}
};

template <Parser... Ps>
requires (sizeof...(Ps) >= 2)
struct NewChoice
{
	static_assert(all_same_type<typename Ps::result_type...>, "All sub-parsers in a Choice parser must have the same result_type.");
	using result_type = typename first_type<Ps...>::result_type;

	static constexpr NewResult<result_type> parse(Input input)
	{
		NewResult<result_type> result{};

		const auto executor = NewChoiceExec<result_type>{ .input = input, .result_ref = result };
		(... || executor.execute<Ps>());

		return result;
	}
};

}
