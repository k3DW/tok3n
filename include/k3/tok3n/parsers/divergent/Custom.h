#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <class CRTP, class ValueType>
struct Custom
{
	using value_type = ValueType;

	static constexpr ParserFamily family = CustomFamily;

	template <std::same_as<CRTP> P = CRTP>
	static constexpr Result<typename P::result_type, typename P::value_type> parse(Input<typename P::value_type> input)
	{
		return parse<P, typename P::value_type>(input);
	}

	template <std::same_as<CRTP> P = CRTP, std::convertible_to<typename P::value_type> V>
	static constexpr Result<typename P::result_type, V> parse(Input<V> input)
	{
		static_assert(requires { { P::get_parser() } -> Parser; }, "Custom parser requires a `get_parser()` function");
		static_assert(std::same_as<typename decltype(P::get_parser())::value_type, typename P::value_type>, "Custom parser requires the same `value_type`");
		return decltype(P::get_parser())::parse(input);
	}

	template <std::same_as<CRTP> P = CRTP>
	static constexpr Result<void, typename P::value_type> lookahead(Input<typename P::value_type> input)
	{
		return lookahead<P, typename P::value_type>(input);
	}

	template <std::same_as<CRTP> P = CRTP, std::convertible_to<typename P::value_type> V>
	static constexpr Result<void, V> lookahead(Input<V> input)
	{
		static_assert(requires { { P::get_parser() } -> Parser; }, "Custom parser requires a `get_parser()` function");
		static_assert(std::same_as<typename decltype(P::get_parser())::value_type, typename P::value_type>, "Custom parser requires the same `value_type`");
		return decltype(P::get_parser())::lookahead(input);
	}
};

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::Custom;

} // namespace k3::tok3n::operators
