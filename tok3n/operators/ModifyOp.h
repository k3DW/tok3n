#pragma once
#include "parsers/_decl.h"
#include <vector>
#include <optional>

namespace k3::parser
{

template <Parser P, auto function>
constexpr auto operator%(P, fn_t<function>)
{
	return Transform<P, function>{};
}


class Flatten
{
public:
	template <Flattenable T>
	constexpr std::string_view operator()(T&& t) const
	{
		//if constexpr (requires { execute(t); })
			return execute(t).value_or("");
		//else
		//	assert(std::forward<T>(t));
	}

private:
	template <class T>
	static constexpr void assert(T&& t)
	{
		static_assert("This type cannot be flattened. Only containers of std::string_view, and containers of these containers, may be flattened.");
	}

	using sv = std::string_view;
	using opt_sv = std::optional<sv>;

	static constexpr opt_sv execute(sv str)
	{
		return str;
	}

	template <class T>
	static constexpr opt_sv execute(const std::vector<T>& vec)
	{
		if (vec.empty())
			return std::nullopt;
		else
		{
			opt_sv begin, last;

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

			return sv{ &begin->front(), &last->back() + 1 };
		}
	}

	template <class T>
	static constexpr opt_sv execute(const std::optional<T>& opt)
	{
		if (not opt.has_value())
			return std::nullopt;
		else
			return execute(*opt);
	}

	template <class T>
	static constexpr bool execute_tuple_helper(const T& t, opt_sv& out_param)
	{
		out_param = execute(t);
		return out_param.has_value();
	};

	template <class... Ts, std::size_t... Is>
	static constexpr opt_sv tuple_begin(const std::tuple<Ts...>& tuple, std::index_sequence<Is...>)
	{
		opt_sv out;
		(... && execute_tuple_helper(std::get<Is>(tuple), out));
		return out;
	}

	template <class... Ts, std::size_t... Is>
	static constexpr opt_sv tuple_last(const std::tuple<Ts...>& tuple, std::index_sequence<Is...>)
	{
		opt_sv out;
		(... && execute_tuple_helper(std::get<sizeof...(Ts) - Is - 1>(tuple), out));
		return out;
	}

	template <class... Ts>
	requires (sizeof...(Ts) != 0)
	static constexpr opt_sv execute(const std::tuple<Ts...>& tuple)
	{
		opt_sv begin = tuple_begin(tuple, std::index_sequence_for<Ts...>{});
		if (!begin)
			return std::nullopt;

		// If begin has a value, then this last will be guaranteed to have a value
		opt_sv last = tuple_last(tuple, std::index_sequence_for<Ts...>{});

		return sv{ &begin->front(), &last->back() + 1 };
	}
};

constexpr Flatten flatten_fn{};

template <Parser P>
constexpr auto operator%(P, flatten_t)
{
	return Transform<P, flatten_fn>{};
}

}
