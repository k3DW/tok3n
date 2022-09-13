#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::parser
{

struct SequenceExec
{
	Input& input;
	std::vector<Result>& results;

	template <Parser P>
	constexpr bool operator()(P) const
	{
		Result result = P::parse(input);
		if (result.has_value())
		{
			input = result.remainder();
			results.emplace_back(std::move(result));
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
	static constexpr Result parse(Input input)
	{
		const Input original_input = input;

		std::vector<Result> results;
		const auto executor = SequenceExec{ .input = input, .results = results };
		(... && executor(Ps{}));

		if (results.size() == sizeof...(Ps))
			return Result::success(results, input);
		else
			return Result::failure(original_input);
	}
};

template <class result_type>
struct NewSequenceExec
{
	Input& input;
	result_type& result_ref;

	template <Parser P, std::size_t I>
	constexpr bool execute() const
	{
		auto result = P::parse(input);
		if (result.has_value())
		{
			input = result.remaining();
			std::get<I>(result_ref) = std::move(result.value());
			return true;
		}
		else
			return false;
	}
};

template <Parser... Ps>
requires (sizeof...(Ps) >= 2)
struct NewSequence
{
	using result_type = std::tuple<typename Ps::result_type...>;

	static constexpr NewResult<result_type> parse(Input input)
	{
		const Input original_input = input;

		result_type result; // This might be a problem because it zero initializes all members

		const auto executor = NewSequenceExec{ .input = input, .result_ref = result };

		bool successful = [&executor]<std::size_t... Is>(std::index_sequence<Is...>)
		{
			return (... && executor.execute<Ps, Is>());
		}(std::index_sequence_for<Ps...>{});

		if (successful)
			return { success, std::move(result), input };
		else
			return { failure, original_input };
	}
};

}
