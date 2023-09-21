#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <class CRTP>
struct Custom
{
	static constexpr ParserFamily type = CustomFamily;

	template <std::same_as<CRTP> P = CRTP>
	static constexpr Result<typename P::result_type, char> parse(Input<char> input)
	{
		static_assert(requires { { P::get_parser() } -> Parser; });
		return decltype(P::get_parser())::parse(input);
	}

	template <std::same_as<CRTP> P = CRTP>
	static constexpr Result<void, char> lookahead(Input<char> input)
	{
		static_assert(requires { { P::get_parser() } -> Parser; });
		return decltype(P::get_parser())::lookahead(input);
	}
};

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::Custom;

} // namespace k3::tok3n::operators
