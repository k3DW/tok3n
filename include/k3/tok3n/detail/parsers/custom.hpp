// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_PARSERS_CUSTOM_HPP
#define K3_TOK3N_DETAIL_PARSERS_CUSTOM_HPP

#include <k3/tok3n/detail/helpers.hpp>
#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/result.hpp>

namespace k3::tok3n::detail {

namespace impl {

template <class P, class V>
struct custom_parser_result_type
{
	static_assert(parser_for<decltype(P::get_parser()), V>, "P::get_parser() must be a parser for V.");
	using type = typename decltype(P::get_parser())::template result_for<V>;
};

template <class P, class V>
requires requires { typename P::result_type; }
struct custom_parser_result_type<P, V>
{
	using type = typename P::result_type;
};

} // namespace impl

template <class CRTP, class ValueType = char>
struct custom_parser
{
	using value_type = ValueType;

	template <class V, std::same_as<CRTP> P = CRTP>
	requires equality_comparable_with<typename P::value_type, V>
	using result_for = typename impl::custom_parser_result_type<P, V>::type;

	static constexpr parser_family family = custom_family;

	template <input_constructible_for<value_type> R, std::same_as<CRTP> P = CRTP, std::same_as<input_value_t<R>> V = input_value_t<R>>
	static constexpr result<typename P::template result_for<V>, V> parse(R&& r)
	{
		static_assert(requires { { P::get_parser() } -> parser; }, "custom parser requires a `get_parser()` function");
		static_assert(std::same_as<typename decltype(P::get_parser())::value_type, typename P::value_type>);

		if constexpr (std::same_as<void, typename P::template result_for<V>>)
		{
			return decltype(P::get_parser())::parse(std::forward<R>(r));
		}
		else
		{
			typename P::template result_for<V> out;
			return decltype(P::get_parser())::parse(std::forward<R>(r), out)
				.with_value(std::move(out));
		}
	}

	template <input_constructible_for<value_type> R, class Out, std::same_as<CRTP> P = CRTP, std::same_as<input_value_t<R>> V = input_value_t<R>>
	static constexpr result<void, V> parse(R&& r, Out& out)
	{
		static_assert(requires { { P::get_parser() } -> parser; }, "custom parser requires a `get_parser()` function");
		static_assert(std::same_as<typename decltype(P::get_parser())::value_type, typename P::value_type>);
		return decltype(P::get_parser())::parse(std::forward<R>(r), out);
	}


	template <input_constructible_for<value_type> R, std::same_as<CRTP> P = CRTP, std::same_as<input_value_t<R>> V = input_value_t<R>>
	static constexpr result<void, V> lookahead(R&& r)
	{
		static_assert(requires { { P::get_parser() } -> parser; }, "custom parser requires a `get_parser()` function");
		static_assert(std::same_as<typename decltype(P::get_parser())::value_type, typename P::value_type>);
		return decltype(P::get_parser())::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_PARSERS_CUSTOM_HPP
