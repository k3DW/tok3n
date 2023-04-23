#pragma once
#include <k3/tok3n/namespace.h>
#include <k3/tok3n/types/ParserType.h>
#include <k3/tok3n/types/Input.h>
#include <k3/tok3n/concepts/implicitly_default_constructible.h>
#include <k3/tok3n/concepts/IsResult.h>
#include <type_traits>

TOK3N_BEGIN_NAMESPACE()

template <class P>
concept Parser =
	requires { typename std::integral_constant<ParserType, P::type>; } &&
	std::to_underlying(P::type) > std::to_underlying(ParserType::None) &&
	std::to_underlying(P::type) < std::to_underlying(ParserType::END) &&
	(std::is_empty_v<P>) &&
	implicitly_default_constructible<P> &&
	requires { typename P::result_type; } &&
	requires (Input input)
	{
		{ P::parse(input) } -> IsResult<typename P::result_type>;
		{ P::lookahead(input) } -> IsResult<void>;
	};

TOK3N_END_NAMESPACE()
