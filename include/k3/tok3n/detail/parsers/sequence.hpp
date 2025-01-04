// Copyright 2022-2025 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef K3_TOK3N_DETAIL_PARSERS_SEQUENCE_HPP
#define K3_TOK3N_DETAIL_PARSERS_SEQUENCE_HPP

#include <k3/tok3n/detail/filter.hpp>
#include <k3/tok3n/detail/helpers.hpp>
#include <k3/tok3n/detail/parser.hpp>
#include <k3/tok3n/detail/result.hpp>
#include <tuple>

namespace k3::tok3n::detail {

template <parser P, parser_compatible_with<P>... Ps>
struct sequence_parser
{
	using value_type = typename P::value_type;

private:
	template <equality_comparable_with<value_type> V>
	using _trait = compound_trait<filter_out_void, std::tuple, V, P, Ps...>;

public:
	template <equality_comparable_with<value_type> V>
	using result_for = typename _trait<V>::result_for;

	static constexpr parser_family family = sequence_family;

	template <input_constructible_for<value_type> R>
	static constexpr auto parse(R&& r)
	{
		if constexpr (std::same_as<void, result_for<input_value_t<R>>>)
		{
			return _impl(call_parse, std::forward<R>(r), typename _trait<input_value_t<R>>::sequence{});
		}
		else
		{
			result_for<input_value_t<R>> out;
			return _impl(call_parse_into, std::forward<R>(r), typename _trait<input_value_t<R>>::sequence{}, out)
				.with_value(std::move(out));
		}
	}

	template <input_constructible_for<value_type> R, class Out>
	static constexpr auto parse(R&& r, Out& out)
	requires requires { sequence_parser<P, Ps...>::_impl(call_parse_into, std::forward<R>(r), typename _trait<input_value_t<R>>::sequence{}, out); }
	{
		return _impl(call_parse_into, std::forward<R>(r), typename _trait<input_value_t<R>>::sequence{}, out);
	}

	template <input_constructible_for<value_type> R>
	static constexpr auto lookahead(R&& r)
	{
		constexpr auto make_minus_one = [](auto&&) { return static_cast<std::size_t>(-1); };
		using seq = std::index_sequence<make_minus_one(P{}), make_minus_one(Ps{})...>;
		return _impl(call_lookahead, std::forward<R>(r), seq{});
	}

private:
	template <class Call, input_constructible_for<value_type> R, std::size_t I, std::size_t... Is, class... Out>
	requires (sizeof...(Out) <= 1)
		and impl::compound_executable<_trait<input_value_t<R>>::unwrapped, compound_type::sequence, I, P, input_value_t<R>, Out...>
		and (... and impl::compound_executable<_trait<input_value_t<R>>::unwrapped, compound_type::sequence, Is, Ps, input_value_t<R>, Out...>)
	static constexpr result<void, input_value_t<R>> _impl(Call, R&& r, std::index_sequence<I, Is...>, Out&... out)
	{
		const input_span input{ std::forward<R>(r) };
		using V = input_value_t<R>;

		auto executor = compound_executor<V, _trait<V>::unwrapped, Call, compound_type::sequence>{ input };
		const bool successful = (executor.template exec<I>(P{}, out...) and ... and executor.template exec<Is>(Ps{}, out...));
		return result<void, V>{ successful, successful ? executor.input : input };
	}
};

} // namespace k3::tok3n::detail

#endif // K3_TOK3N_DETAIL_PARSERS_SEQUENCE_HPP
