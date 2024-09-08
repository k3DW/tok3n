#pragma once
#include <k3/tok3n/types/ParserFamily.h>
#include <k3/tok3n/types/Span.h>
#include <k3/tok3n/concepts/IsResult.h>
#include <k3/tok3n/detail/type_traits.h>
#include <type_traits>

namespace k3::tok3n {

namespace detail {

template <template <class...> class A>
struct HasTemplateAlias {};
	
template <class P>
concept Parser =
	requires { typename std::integral_constant<ParserFamily, P::family>; } &&
	static_cast<int>(P::family) > static_cast<int>(ParserFamily::None) &&
	static_cast<int>(P::family) < static_cast<int>(ParserFamily::END) &&
	(std::is_empty_v<P>) &&
	detail::implicitly_default_constructible<P> &&
	requires { typename P::value_type; } &&
	requires { HasTemplateAlias<P::template result_for>{}; };

}

template <class P>
concept Parser =
	(std::is_class_v<P> && detail::Parser<P>) ||
	(std::is_reference_v<P> && detail::Parser<std::remove_reference_t<P>>);

} // namespace k3::tok3n
