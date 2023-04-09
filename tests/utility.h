#pragma once
#include "tok3n/tok3n.h"

TOK3N_BEGIN_NAMESPACE(tests)

template <Parser P, Parser Q>
consteval bool operator==(P, Q)
{
	return std::is_same_v<P, Q>;
}

namespace parser_equality_operator
{

	template <Parser P, Parser Q>
	consteval bool validate_individual(P, Q)
	{
		return (std::is_same_v<std::remove_cvref_t<P>, std::remove_cvref_t<Q>>)
			? (P{} == Q{})
			: (P{} != Q{});
	}

	template <Parser P, Parser... Qs>
	consteval bool validate_with_pack(P, Qs...)
	{
		return (... && validate_individual(P{}, Qs{}));
	}

	template <Parser... Ps>
	consteval bool validate(Ps...)
	{
		return (... && validate_with_pack(Ps{}, Ps{}...));
	}

}

TOK3N_END_NAMESPACE(tests)
