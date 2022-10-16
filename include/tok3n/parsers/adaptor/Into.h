#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

TOK3N_BEGIN_NAMESPACE()

namespace detail::executors
{

	template <class T>
	struct Into
	{
		template <class... Us>
		static constexpr T execute(std::tuple<Us...>&& tup)
		{
			return std::make_from_tuple<T>(std::move(tup));
		}

		template <class U>
		static constexpr T execute(U&& u)
		{
			return T{ std::forward<U>(u) };
		}
	};

}

template <Parser P, class T>
requires Intoable<T, typename P::result_type>
struct Into
{
	using result_type = T;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result.has_value())
		{
			using Executor = detail::executors::Into<T>;
			return { success, Executor::execute(std::move(*result)), result.remaining()};
		}
		return { failure, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}
};

TOK3N_END_NAMESPACE()
