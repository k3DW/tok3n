#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

namespace k3::tok3n
{

template <class result_type>
struct ChoiceExec
{
	Input input;
	Result<result_type> result = {};

	template <Parser P>
	constexpr bool execute()
	{
		if constexpr (std::same_as<result_type, void>)
			result = P::lookahead(input);
		else
			result = P::parse(input);
		return result.has_value();
	}
};

template <Parser... Ps>
requires (sizeof...(Ps) >= 2) && mp::all_same<typename Ps::result_type...>
struct Choice
{
	using result_type = typename mp::head<Ps...>::result_type;

	static constexpr Result<result_type> parse(Input input)
	{
		auto executor = ChoiceExec<result_type>{ .input = input };
		(... || executor.execute<Ps>());

		return executor.result;
	}

	static constexpr Result<void> lookahead(Input input)
	{
		auto executor = ChoiceExec<void>{ .input = input };
		(... || executor.execute<Ps>());

		return executor.result;
	}
};

}
