#pragma once
#include <k3/tok3n/types/ParserFamily.h>
#include <k3/tok3n/types/Span.h>
#include <k3/tok3n/detail/implicitly_default_constructible.h>
#include <k3/tok3n/concepts/IsResult.h>
#include <type_traits>

namespace k3::tok3n {

template <class P>
concept Parser =
	requires { typename std::integral_constant<ParserFamily, P::family>; } &&
	static_cast<int>(P::family) > static_cast<int>(ParserFamily::None) &&
	static_cast<int>(P::family) < static_cast<int>(ParserFamily::END) &&
	(std::is_empty_v<P>) &&
	detail::implicitly_default_constructible<P> &&
	requires { typename P::result_type; } &&
	(
		requires (Input<char> input)
		{
			{ P::parse(input) } -> IsResult<typename P::result_type, char>;
			{ P::lookahead(input) } -> IsResult<void, char>;
		}
		||
		(
			requires { typename P::value_type; } &&
			requires (Input<typename P::value_type> input)
			{
				{ P::parse(input) } -> IsResult<typename P::result_type, typename P::value_type>;
				{ P::lookahead(input) } -> IsResult<void, typename P::value_type>;
			}
		)
	);

} // namespace k3::tok3n
