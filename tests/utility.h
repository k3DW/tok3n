#pragma once
#include "tok3n/tok3n.h"

TOK3N_BEGIN_NAMESPACE(tests)

template <Parser P>
struct parse_t
{
	consteval parse_t(Input input) : input(input) {}
	Input input;

	static constexpr bool is_result_void = std::same_as<typename P::result_type, void>;
	using value_type = std::conditional_t<is_result_void, std::monostate, typename P::result_type>;
	// We need this `value_type` indirection, otherwise the first `success()` overload causes compile errors when `result_type` is `void`.

	consteval bool success(value_type&& value, Input remaining) const&& requires (not is_result_void)
	{
		return parse_success(std::move(value), remaining) && lookahead_success(remaining);
	}

	consteval bool success(Input remaining) const&& requires (is_result_void)
	{
		return parse_success(remaining) && lookahead_success(remaining);
	}

	consteval bool failure() const&&
	{
		return parse_failure(input) && lookahead_failure(input);
	}

	consteval bool only_lookahead(Input lookahead_remaining) const&&
	{
		return parse_failure(input) && lookahead_success(lookahead_remaining);
	}

private:
	consteval bool parse_success(value_type&& value, Input remaining) const requires (not is_result_void)
	{
		const auto result = P::parse(input);
		return (result) && (*result == value) && (result.remaining() == remaining);
	}

	consteval bool parse_success(Input remaining) const requires (is_result_void)
	{
		const auto result = P::parse(input);
		return (result) && (result.remaining() == remaining);
	}

	consteval bool parse_failure(Input remaining) const
	{
		const auto result = P::parse(input);
		return (not result) && (result.remaining() == remaining);
	}

	consteval bool lookahead_success(Input remaining) const
	{
		const auto result = P::lookahead(input);
		return (result) && (result.remaining() == remaining);
	}

	consteval bool lookahead_failure(Input remaining) const
	{
		const auto result = P::lookahead(input);
		return (not result) && (result.remaining() == remaining);
	}
};

template <Parser P>
consteval parse_t<P> parse(Input input)
{
	return { input };
}

template <Parser P>
consteval parse_t<P> parse(P, Input input)
{
	return { input };
}



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
