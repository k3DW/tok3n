#pragma once
#include <concepts>
#include <type_traits>

#include "parsers/Result.h"
using k3::parser::Result;



template <class P, class Q>
consteval bool same()
{
	return std::same_as<std::remove_cvref_t<P>, std::remove_cvref_t<Q>>;
}

template <class P>
consteval bool same(auto&& rhs)
{
	return std::same_as<std::remove_cvref_t<P>, std::remove_cvref_t<decltype(rhs)>>;
}

consteval bool same(auto&& lhs, auto&& rhs)
{
	return std::same_as<std::remove_cvref_t<decltype(lhs)>, std::remove_cvref_t<decltype(rhs)>>;
}



template <class T>
consteval bool check_result(const Result<T>& result, const std::type_identity_t<T>& t, std::string_view remaining)
{
	return (result) && (*result == t) && (result.remaining() == remaining);
}

template <class P, class R>
concept is_result_of = std::same_as<typename P::result_type, R>;
