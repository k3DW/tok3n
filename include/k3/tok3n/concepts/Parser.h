#pragma once
#include <k3/tok3n/types/ParserType.h>
#include <k3/tok3n/types/Input.h>
#include <k3/tok3n/detail/implicitly_default_constructible.h>
#include <k3/tok3n/concepts/IsResult.h>
#include <type_traits>

namespace k3::tok3n {

template <class P>
concept Parser =
	requires { typename std::integral_constant<ParserType, P::type>; } &&
	static_cast<int>(P::type) > static_cast<int>(ParserType::None) &&
	static_cast<int>(P::type) < static_cast<int>(ParserType::END) &&
	(std::is_empty_v<P>) &&
	detail::implicitly_default_constructible<P> &&
	requires { typename P::result_type; } &&
	requires (Input<char> input)
	{
		{ P::parse(input) } -> IsResult<typename P::result_type>;
		{ P::lookahead(input) } -> IsResult<void>;
	};

} // namespace k3::tok3n
