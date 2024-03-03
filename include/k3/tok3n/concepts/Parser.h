#pragma once
#include <k3/tok3n/types/ParserFamily.h>
#include <k3/tok3n/types/Span.h>
#include <k3/tok3n/detail/implicitly_default_constructible.h>
#include <k3/tok3n/concepts/IsResult.h>
#include <type_traits>

namespace k3::tok3n {

namespace detail {
	
template <class P>
concept Parser =
	requires { typename std::integral_constant<ParserFamily, P::family>; } &&
	static_cast<int>(P::family) > static_cast<int>(ParserFamily::None) &&
	static_cast<int>(P::family) < static_cast<int>(ParserFamily::END) &&
	(std::is_empty_v<P>) &&
	detail::implicitly_default_constructible<P> &&
	requires { typename P::value_type; } &&
	requires { typename P::result_type; } &&
	requires (Input<typename P::value_type> input)
	{
		{ P::parse(input) } -> k3::tok3n::IsResult<typename P::result_type, typename P::value_type>;
		{ P::lookahead(input) } -> k3::tok3n::IsResult<void, typename P::value_type>;
	};

}

template <class P>
concept Parser =
	(std::is_class_v<P> && detail::Parser<P>) ||
	(std::is_reference_v<P> && detail::Parser<std::remove_reference_t<P>>);

template <class P1, class P2>
concept ParserCompatibleWith = std::same_as<typename P1::value_type, typename P2::value_type>;

} // namespace k3::tok3n
