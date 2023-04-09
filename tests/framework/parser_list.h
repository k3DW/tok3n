#pragma once
#include <k3/tok3n/concepts/Parser.h>

TOK3N_BEGIN_NAMESPACE(tests)

template <Parser... Ps>
struct parser_list
{
	consteval parser_list() = default;
	consteval parser_list(Ps...) {}
};

template <Parser... Ps>
parser_list(Ps...) -> parser_list<Ps...>;

template <Parser... LHS, Parser... RHS>
consteval auto operator+(parser_list<LHS...>, parser_list<RHS...>)
{
	return parser_list<LHS..., RHS...>{};
}

TOK3N_END_NAMESPACE(tests)
