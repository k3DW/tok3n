#pragma once
#include <k3/tok3n/concepts/Parser.h>

TOK3N_BEGIN_NAMESPACE(tests)

template <Parser LHS, Parser RHS>
consteval bool operator==(LHS, RHS)
{
	return std::is_same_v<LHS, RHS>;
}

template <Parser LHS, Parser RHS>
consteval bool operator!=(LHS, RHS)
{
	return not std::is_same_v<LHS, RHS>;
}

template <Parser LHS, Parser RHS>
consteval auto operator<=>(LHS, RHS) = delete;

TOK3N_END_NAMESPACE(tests)
