#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

TOK3N_BEGIN_NAMESPACE()

namespace detail::executors
{

	struct VoidResultTag {};

	template <class ResultType>
	struct Sequence
	{
		using StoredResult = std::conditional_t<std::same_as<ResultType, void>, VoidResultTag, ResultType>;

		Input input;
		StoredResult full_result = {};

		template <Parser P, std::size_t I, bool unwrapped>
		constexpr bool execute()
		{
			if constexpr (I == -1)
				return execute_lookahead<P>();
			else
				return execute_element<P, I, unwrapped>();
		}

		template <Parser P>
		constexpr bool execute_lookahead()
		{
			auto result = P::lookahead(input);
			input = result.remaining();
			return result.has_value();
		}

		template <Parser P, std::size_t I, bool unwrapped>
		constexpr bool execute_element()
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
		using Executor = detail::executors::Sequence<result_type>;
		Executor executor{ .input = input };

		bool successful = [&executor]<std::size_t... Is>(std::index_sequence<Is...>)
		{
			return (... && executor.execute<Ps, Is, _unwrapped>());
		}(mp::filtered_sequence<mp::is_not_type<void>, typename Ps::result_type...>{});

		if (not successful)
			return { failure, input };

		if constexpr (std::same_as<result_type, void>)
			return { success, executor.input };
		else
			return { success, std::move(executor.full_result), executor.input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		using Executor = detail::executors::Sequence<void>;
		Executor executor{ .input = input };

		bool successful = (... && executor.execute<Ps, -1, _unwrapped>());

		if (successful)
			return { success, executor.input };
		else
			return { failure, input };
	}
};

TOK3N_END_NAMESPACE()
