#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

TOK3N_BEGIN_NAMESPACE()

template <class result_type, bool unwrapped>
struct SequenceExecutor
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
				if constexpr (unwrapped)
					full_result = std::move(*result);
				else
					std::get<I>(full_result) = std::move(*result);
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
	using unwrap_trait = mp::unwrap_if_single<mp::retarget<filtered, std::tuple>>;

	using result_type = unwrap_trait::type;
	static constexpr bool unwrapped = unwrap_trait::value;

	static constexpr Result<result_type> parse(Input input)
	{
		// This might be a problem because it zero initializes all members
		auto executor = SequenceExecutor<result_type, unwrapped>{ .input = input };

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
		auto executor = SequenceExecutor<std::monostate, unwrapped>{ .input = input };

		bool successful = (... && executor.execute<Ps, -1>());

		if (successful)
			return { success, executor.input };
		else
			return { failure, input };
	}
};

TOK3N_END_NAMESPACE()
