#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

TOK3N_BEGIN_NAMESPACE()

namespace detail::executors
{

	template <class result_type, bool unwrapped>
	struct Sequence
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

}

template <Parser... Ps>
requires detail::Sequence_able<Ps...>
struct Sequence
{
	using _trait = detail::Sequence_result_trait<Ps...>;

	using result_type                = _trait::type;
	static constexpr bool _unwrapped = _trait::unwrapped;

	static constexpr Result<result_type> parse(Input input)
	{
		// This might be a problem because it default initializes all members
		using Executor = detail::executors::Sequence<result_type, _unwrapped>;
		Executor executor{ .input = input };

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
		using Executor = detail::executors::Sequence<std::monostate, _unwrapped>; // std::monostate is not significant, just needs to be empty (and not void)
		Executor executor{ .input = input };

		bool successful = (... && executor.execute<Ps, -1>());

		if (successful)
			return { success, executor.input };
		else
			return { failure, input };
	}
};

TOK3N_END_NAMESPACE()
