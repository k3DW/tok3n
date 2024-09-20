#pragma once
#include <k3/tok3n/detail/helpers.h>
#include <k3/tok3n/detail/parser.h>
#include <k3/tok3n/detail/result.h>

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

	template <input_constructible_for<value_type> R, std::same_as<CRTP> P = CRTP, class V = input_value_t<R>>
	static constexpr result<typename P::template result_for<V>, V> parse(R&& r)
	{
		static_assert(requires { { P::get_parser() } -> parser; }, "custom parser requires a `get_parser()` function");
		static_assert(std::same_as<typename decltype(P::get_parser())::value_type, typename P::value_type>);
		return decltype(P::get_parser())::parse(std::forward<R>(r));
	}

	template <input_constructible_for<value_type> R, std::same_as<CRTP> P = CRTP, class V = input_value_t<R>>
	static constexpr result<void, V> lookahead(R&& r)
	{
		static_assert(requires { { P::get_parser() } -> parser; }, "custom parser requires a `get_parser()` function");
		static_assert(std::same_as<typename decltype(P::get_parser())::value_type, typename P::value_type>);
		return decltype(P::get_parser())::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n::detail
