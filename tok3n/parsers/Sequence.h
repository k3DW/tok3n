#pragma once
#include "parsers/_decl.h"
#include "parsers/Result.h"

namespace k3::parser
{

template <class result_type, bool flattened>
struct SequenceExec
{
	Input input;
	result_type full_result = {};

	template <Parser P, std::size_t I>
	constexpr bool execute()
	{
		if constexpr (I == -1)
		{
			auto result = P::lookahead(input);
			input = result.remaining();
			return result.has_value();
		}
		else
		{
			auto result = P::parse(input);
			if (result.has_value())
			{
				input = result.remaining();
				if constexpr (flattened)
					full_result = std::move(result.value());
				else
					std::get<I>(full_result) = std::move(result.value());
				return true;
			}
			else
				return false;
		}
	}
};

template <class T> struct is_not_void : std::bool_constant<true> {};
template <> struct is_not_void<void>  : std::bool_constant<false> {};

template <Parser... Ps>
requires (sizeof...(Ps) >= 2)
struct Sequence
{
	using result_trait = flatten_if_single<filter_type<std::tuple, is_not_void, typename Ps::result_type...>>;

	using result_type = result_trait::type;
	static constexpr bool flattened = result_trait::value;

	static constexpr Result<result_type> parse(Input input)
	{
		// This might be a problem because it zero initializes all members
		auto executor = SequenceExec<result_type, flattened>{ .input = input };

		bool successful = [&executor]<std::size_t... Is>(std::index_sequence<Is...>)
		{
			return (... && executor.execute<Ps, Is>());
		}(filtered_index_sequence_type<is_not_void, typename Ps::result_type...>{});

		if (successful)
			return { success, std::move(executor.full_result), executor.input };
		else
			return { failure, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		// Using std::monostate because we don't have regular void, but this could be anything since it isn't used
		auto executor = SequenceExec<std::monostate, flattened>{ .input = input };

		bool successful = (... && executor.execute<Ps, -1>());

		if (successful)
			return { success, executor.input };
		else
			return { failure, input };
	}
};

}
