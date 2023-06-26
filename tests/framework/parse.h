#pragma once
#include <k3/tok3n/concepts/Parser.h>

using namespace k3::tok3n;

template <Parser P>
struct parse_t final
{
	explicit consteval parse_t(Input input) : input(input) {}

private:
	Input input;

	static constexpr bool is_result_void = std::same_as<typename P::result_type, void>;
	using value_type = std::conditional_t<is_result_void, std::monostate, typename P::result_type>;
	// We need this `value_type` indirection, otherwise the first `success()` overload causes compile errors when `result_type` is `void`.

public:
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
consteval auto parse(Input input)
{
	return parse_t<P>{ input };
}

template <Parser P>
consteval auto parse(P, Input input)
{
	return parse_t<P>{ input };
}
