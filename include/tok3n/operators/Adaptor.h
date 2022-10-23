#pragma once
#include "tok3n/parsers/Declarations.h"

TOK3N_BEGIN_NAMESPACE()



template <auto function>
struct fn_t final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Transform<P, function>{};
	}
};

template <auto function>
constexpr auto fn = fn_t<function>{};

template <Parser P, auto function>
consteval auto operator%(P p, fn_t<function> modifier)
{
	return modifier(p);
}



struct join_t final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		if constexpr (std::same_as<Input, typename P::result_type>)
			return P{};
		else
			return Join<P>{};
	}
};

constexpr auto join = join_t{};

template <Parser P>
consteval auto operator%(P p, join_t modifier)
{
	return modifier(p);
}



template <class T>
struct into_t final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Into<P, T>{};
	}
};

template <class T>
constexpr auto into = into_t<T>{};

template <Parser P, class T>
consteval auto operator%(P p, into_t<T> modifier)
{
	return modifier(p);
}



template <auto value>
struct constant_t final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Constant<P, value>{};
	}
};

template <auto value>
constexpr auto constant = constant_t<value>{};

template <Parser P, auto value>
consteval auto operator%(P p, constant_t<value> modifier)
{
	return modifier(p);
}



template <class T>
struct defaulted_t final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Defaulted<P, T>{};
	}
};

template <class T>
constexpr auto defaulted = defaulted_t<T>{};

template <Parser P, class T>
consteval auto operator%(P p, defaulted_t<T> modifier)
{
	return modifier(p);
}



template <std::size_t N>
struct exactly_t final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		return Exactly<P, N>{};
	}
};

template <std::size_t N>
constexpr auto exactly = exactly_t<N>{};

template <std::size_t N, Parser P>
consteval auto operator%(P p, exactly_t<N> modifier)
{
	return modifier(p);
}



struct ignore_t final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		if constexpr (IsIgnore<P>)
			return P{};
		else
			return Ignore<P>{};
	}
};

constexpr auto ignore = ignore_t{};

template <Parser P>
consteval auto operator%(P p, ignore_t modifier)
{
	return modifier(p);
}



struct complete_t final
{
	template <Parser P>
	consteval auto operator()(P) const
	{
		if constexpr (IsComplete<P>)
			return P{};
		else
			return Complete<P>{};
	}
};

constexpr auto complete = complete_t{};

template <Parser P>
consteval auto operator%(P p, complete_t modifier)
{
	return modifier(p);
}



struct delimit_t final
{
	template <Parser P, Parser Delimiter>
	consteval auto operator()(P, Delimiter) const
	{
		return Delimit<P, Delimiter>{};
	}

	template <Parser Delimiter>
	struct inner final
	{
		template <Parser P>
		consteval auto operator()(P) const
		{
			return Delimit<P, Delimiter>{};
		}
	};

	template <Parser Delimiter>
	consteval auto operator()(Delimiter) const
	{
		return inner<Delimiter>{};
	}
};

constexpr auto delimit = delimit_t{};

template <Parser P, Parser Delimiter>
consteval auto operator%(P p, delimit_t::inner<Delimiter> modifier)
{
	return modifier(p);
}



TOK3N_END_NAMESPACE()
