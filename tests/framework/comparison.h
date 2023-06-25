#pragma once
#include <k3/tok3n/concepts/Parser.h>

using namespace k3::tok3n;

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

template <Modifier LHS, Modifier RHS>
consteval bool operator==(LHS, RHS)
{
	return std::is_same_v<LHS, RHS>;
}

template <Modifier LHS, Modifier RHS>
consteval bool operator!=(LHS, RHS)
{
	return not std::is_same_v<LHS, RHS>;
}

template <Modifier LHS, Modifier RHS>
consteval auto operator<=>(LHS, RHS) = delete;
