#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

namespace detail {

	template <class P, class V>
	struct CustomParserResultType
	{
		static_assert(ParserFor<decltype(P::get_parser()), V>, "P::get_parser() must be a parser for V.");
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
	requires EqualityComparableWith<typename P::value_type, V>
	using result_for = typename detail::CustomParserResultType<P, V>::type;

	static constexpr ParserFamily family = CustomFamily;

	template <InputConstructibleFor<value_type> R, std::same_as<CRTP> P = CRTP>
	static constexpr auto parse(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		static_assert(requires { { P::get_parser() } -> Parser; }, "Custom parser requires a `get_parser()` function");
		static_assert(std::same_as<typename decltype(P::get_parser())::value_type, typename P::value_type>);

		using ActualType = typename decltype(P::get_parser())::template result_for<V>;
		using ExpectedType = typename P::template result_for<V>;
		if constexpr (std::same_as<ExpectedType, ActualType>)
		{
			return decltype(P::get_parser())::parse(input);
		}
		else
		{
			static_assert(std::constructible_from<ExpectedType, ActualType&&>);
			return Result<ExpectedType, V>{ decltype(P::get_parser())::parse(input) };
		}
	}

	template <InputConstructibleFor<value_type> R, std::same_as<CRTP> P = CRTP>
	static constexpr auto lookahead(R&& r)
	{
		Input input{ std::forward<R>(r) };
		using V = typename decltype(input)::value_type;

		static_assert(requires { { P::get_parser() } -> Parser; }, "Custom parser requires a `get_parser()` function");
		static_assert(std::same_as<typename decltype(P::get_parser())::value_type, typename P::value_type>);
		return decltype(P::get_parser())::lookahead(input);
	}
};

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::Custom;

} // namespace k3::tok3n::operators
