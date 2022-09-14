#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::parser
{

template <class result_type>
struct ChoiceExec
{
	Input input;
	Result<result_type>& result_ref;

	template <Parser P>
	constexpr bool execute() const
	{
		Result<result_type> result = P::parse(input);
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
	static_assert(all_same_type<typename Ps::result_type...>, "All sub-parsers in a Choice parser must have the same result_type.");
	using result_type = typename first_type<Ps...>::result_type;

	static constexpr Result<result_type> parse(Input input)
	{
		Result<result_type> result{};

		const auto executor = ChoiceExec<result_type>{ .input = input, .result_ref = result };
		(... || executor.execute<Ps>());

		return result;
	}
};

}
