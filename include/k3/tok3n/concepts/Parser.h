#pragma once
#include <k3/tok3n/types/ParserFamily.h>
#include <k3/tok3n/types/Span.h>
#include <k3/tok3n/concepts/IsResult.h>
#include <type_traits>

namespace k3::tok3n {

namespace detail {

template <class P>
concept HasParserFamily =
	requires { typename std::integral_constant<ParserFamily, P::family>; } and
	static_cast<int>(P::family) > static_cast<int>(ParserFamily::None) and
	static_cast<int>(P::family) < static_cast<int>(ParserFamily::END);

template <class P>
concept HasParserDependentTypes =
	requires { typename P::value_type; } and
	requires { typename P::result_type; };

template <class P>
concept HasNonTemplateParserFunctions =
	requires (Input<typename P::value_type> input)
	{
		{ P::parse(input) } -> k3::tok3n::IsResult<typename P::result_type, typename P::value_type>;
		{ P::lookahead(input) } -> k3::tok3n::IsResult<void, typename P::value_type>;
	};

template <class P>
concept HasTemplateParserFunctions_NonCustom =
	P::family != ParserFamily::Custom and
	requires (Input<typename P::value_type> input)
	{
		{ P::template parse<typename P::value_type>(input) } -> k3::tok3n::IsResult<typename P::result_type, typename P::value_type>;
		{ P::template lookahead<typename P::value_type>(input) } -> k3::tok3n::IsResult<void, typename P::value_type>;
	};

template <class P>
concept HasTemplateParserFunctions_Custom =
	P::family == ParserFamily::Custom and
	requires (Input<typename P::value_type> input)
	{
		{ P::template parse<P, typename P::value_type>(input) } -> k3::tok3n::IsResult<typename P::result_type, typename P::value_type>;
		{ P::template lookahead<P, typename P::value_type>(input) } -> k3::tok3n::IsResult<void, typename P::value_type>;
	};

template <class T>
concept ImplicitlyDefaultConstructible = requires (void(fn)(T)) { fn({}); };

template <class P>
concept Parser =
	HasParserFamily<P> and
	HasParserDependentTypes<P> and
	std::is_empty_v<P> and
	ImplicitlyDefaultConstructible<P> and
	HasNonTemplateParserFunctions<P> and
	(HasTemplateParserFunctions_NonCustom<P> or HasTemplateParserFunctions_Custom<P>);

} // namespace detail

template <class P>
concept Parser =
	(std::is_class_v<P> and detail::Parser<P>) or
	(std::is_reference_v<P> and detail::Parser<std::remove_reference_t<P>>);

template <class P1, class P2>
concept ParserCompatibleWith =
	Parser<P1> and
	Parser<P2> and
	std::same_as<typename P1::value_type, typename P2::value_type>;

} // namespace k3::tok3n
