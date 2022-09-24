#pragma once
#include "tok3n/parsers/Declarations.h"
#include "tok3n/parsers/Result.h"

BEGIN_NAMESPACE_TOK3N()

template <Parser P>
requires Flattenable<typename P::result_type>
struct Flatten
{
	using result_type = Input;

	static constexpr Result<result_type> parse(Input input)
	{
		auto result = P::parse(input);
		if (result)
			return { success, execute(*result).value_or(""), result.remaining() };
		else
			return { failure, input };
	}

	static constexpr Result<void> lookahead(Input input)
	{
		return P::lookahead(input);
	}

private:
	using Opt = std::optional<Input>;

	static constexpr Opt execute(Input input)
	{
		return input;
	}

	template <class T>
	static constexpr Opt execute(const std::vector<T>& vec)
	{
		if (vec.empty())
			return std::nullopt;
		else
		{
			Opt begin, last;

			for (const T& t : vec)
			{
				begin = execute(t);
				if (begin)
					break;
			}
			if (!begin)
				return std::nullopt;

			// If begin has a value, then this last will be guaranteed to have a value
			for (const T& t : vec | std::views::reverse)
			{
				last = execute(t);
				if (last)
					break;
			}

			return Input{ &begin->front(), &last->back() + 1 };
		}
	}

	template <class T>
	static constexpr Opt execute(const std::optional<T>& opt)
	{
		if (not opt.has_value())
			return std::nullopt;
		else
			return execute(*opt);
	}

	template <class T>
	static constexpr bool execute_tuple_helper(const T& t, Opt& out_param)
	{
		out_param = execute(t);
		return out_param.has_value();
	};

	template <class... Ts, std::size_t... Is>
	static constexpr Opt tuple_begin(const std::tuple<Ts...>& tuple, std::index_sequence<Is...>)
	{
		Opt out;
		(... && execute_tuple_helper(std::get<Is>(tuple), out));
		return out;
	}

	template <class... Ts, std::size_t... Is>
	static constexpr Opt tuple_last(const std::tuple<Ts...>& tuple, std::index_sequence<Is...>)
	{
		Opt out;
		(... && execute_tuple_helper(std::get<sizeof...(Ts) - Is - 1>(tuple), out));
		return out;
	}

	template <class... Ts>
	requires (sizeof...(Ts) != 0)
	static constexpr Opt execute(const std::tuple<Ts...>& tuple)
	{
		Opt begin = tuple_begin(tuple, std::index_sequence_for<Ts...>{});
		if (!begin)
			return std::nullopt;

		// If begin has a value, then this last will be guaranteed to have a value
		Opt last = tuple_last(tuple, std::index_sequence_for<Ts...>{});

		return Input{ &begin->front(), &last->back() + 1 };
	}
};

END_NAMESPACE_TOK3N()
