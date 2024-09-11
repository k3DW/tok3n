#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

namespace detail {

	template <class P, class V>
	struct CustomParserResultType
	{
		static_assert(parser_for<decltype(P::get_parser()), V>, "P::get_parser() must be a parser for V.");
		using type = typename decltype(P::get_parser())::template result_for<V>;
	};

	template <class P, class V>
	requires requires { typename P::result_type; }
	struct CustomParserResultType<P, V>
	{
		using type = typename P::result_type;
	};

} // namespace detail

template <class CRTP, class ValueType>
struct Custom
{
	using value_type = ValueType;

	template <class V, std::same_as<CRTP> P = CRTP>
	requires detail::equality_comparable_with<typename P::value_type, V>
	using result_for = typename detail::CustomParserResultType<P, V>::type;

	static constexpr detail::parser_family family = detail::custom_family;

	template <detail::input_constructible_for<value_type> R, std::same_as<CRTP> P = CRTP, class V = detail::input_value_t<R>>
	static constexpr detail::result<typename P::template result_for<V>, V> parse(R&& r)
	{
		static_assert(requires { { P::get_parser() } -> detail::parser; }, "Custom parser requires a `get_parser()` function");
		static_assert(std::same_as<typename decltype(P::get_parser())::value_type, typename P::value_type>);
		return decltype(P::get_parser())::parse(std::forward<R>(r));
	}

	template <detail::input_constructible_for<value_type> R, std::same_as<CRTP> P = CRTP, class V = detail::input_value_t<R>>
	static constexpr detail::result<void, V> lookahead(R&& r)
	{
		static_assert(requires { { P::get_parser() } -> detail::parser; }, "Custom parser requires a `get_parser()` function");
		static_assert(std::same_as<typename decltype(P::get_parser())::value_type, typename P::value_type>);
		return decltype(P::get_parser())::lookahead(std::forward<R>(r));
	}
};

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::Custom;

} // namespace k3::tok3n::operators
