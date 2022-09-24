#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

namespace k3::tok3n
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

template <Parser... Ps>
requires (sizeof...(Ps) >= 2)
struct Sequence
{
	using filtered = mp::filter<mp::is_not_type<void>, typename Ps::result_type...>;
	using result_trait = mp::flatten_if_single<mp::retarget<filtered, std::tuple>>;

	using result_type = result_trait::type;
	static constexpr bool flattened = result_trait::value;

	static constexpr Result<result_type> parse(Input input)
	{
		// This might be a problem because it zero initializes all members
		auto executor = SequenceExec<result_type, flattened>{ .input = input };

		bool successful = [&executor]<std::size_t... Is>(std::index_sequence<Is...>)
		{
			return (... && executor.execute<Ps, Is>());
		}(mp::filtered_sequence<mp::is_not_type<void>, typename Ps::result_type...>{});

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
