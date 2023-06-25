#pragma once
#include <k3/tok3n/types.h>
#include <k3/tok3n/concepts.h>

namespace k3::tok3n {

template <class CRTP>
struct Custom
{
	static constexpr ParserType type = CustomType;

	static constexpr auto parse(Input input)
	{
		static_assert(requires { { CRTP::get_parser() } -> Parser; });
		return decltype(CRTP::get_parser())::parse(input);
	}

	static constexpr Result<void> lookahead(Input input)
	{
		static_assert(requires { { CRTP::get_parser() } -> Parser; });
		return decltype(CRTP::get_parser())::lookahead(input);
	}
};

} // namespace k3::tok3n

namespace k3::tok3n::inline operators {
using k3::tok3n::Custom;
} // namespace k3::tok3n::inline operators
