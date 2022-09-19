#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::parser
{

template <class result_type>
struct SequenceExec
{
	Input input;
	result_type tuple = {};

	template <Parser P, std::size_t I>
	constexpr bool execute()
	{
		auto result = P::parse(input);
		if (result.has_value())
		{
			input = result.remaining();
			std::get<I>(tuple) = std::move(result.value());
			return true;
		}
		else
			return false;
	}
};

template <Parser... Ps>
requires (sizeof...(Ps) >= 2)
struct Sequence
{
	using result_type = std::tuple<typename Ps::result_type...>;

	static constexpr Result<result_type> parse(Input input)
	{
		// This might be a problem because it zero initializes all members
		auto executor = SequenceExec<result_type>{ .input = input };

		bool successful = [&executor]<std::size_t... Is>(std::index_sequence<Is...>)
		{
			return (... && executor.execute<Ps, Is>());
		}(std::index_sequence_for<Ps...>{});

		if (successful)
			return { success, std::move(executor.tuple), executor.input };
		else
			return { failure, input };
	}
};

}
