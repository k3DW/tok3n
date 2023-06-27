#pragma once
#include <k3/tok3n/parsers/divergent/_fwd.h>

namespace k3::tok3n {

template <class CRTP>
struct Custom
{
	static constexpr ParserType type = CustomType;

	template <std::same_as<CRTP> P = CRTP>
	static constexpr Result<typename P::result_type> parse(Input input)
	{
		static_assert(requires { { P::get_parser() } -> Parser; });
		return decltype(P::get_parser())::parse(input);
	}

	template <std::same_as<CRTP> P = CRTP>
	static constexpr Result<void> lookahead(Input input)
	{
		static_assert(requires { { P::get_parser() } -> Parser; });
		return decltype(P::get_parser())::lookahead(input);
	}
};

} // namespace k3::tok3n

namespace k3::tok3n::operators {

using ::k3::tok3n::Custom;

} // namespace k3::tok3n::operators
