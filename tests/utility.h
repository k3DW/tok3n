#pragma once
#include "tok3n/tok3n.h"

#define TOK3N_USING_ALL_PARSERS      \
	using k3::tok3n::OneChar;        \
	using k3::tok3n::NotChar;        \
	using k3::tok3n::Literal;        \
	using k3::tok3n::Choice;         \
	using k3::tok3n::Sequence;       \
	using k3::tok3n::Maybe;          \
	using k3::tok3n::Exactly;        \
	using k3::tok3n::OneOrMore;      \
	using k3::tok3n::ZeroOrMore;     \
	using k3::tok3n::Delimit;        \
	using k3::tok3n::Ignore;         \
	using k3::tok3n::Complete;       \
	using k3::tok3n::Join;           \
	using k3::tok3n::Transform;      \
	using k3::tok3n::ApplyTransform; \
	using k3::tok3n::Into;           \
	using k3::tok3n::ApplyInto;      \
	using k3::tok3n::Constant;       \
	using k3::tok3n::Defaulted;      \
	using k3::tok3n::Custom;         \
	using k3::tok3n::exactly;        \
	using k3::tok3n::ignore;         \
	using k3::tok3n::delimit;        \
	using k3::tok3n::complete;       \
	using k3::tok3n::join;           \
	using k3::tok3n::fn;             \
	using k3::tok3n::into;           \
	using k3::tok3n::apply_into;     \
	using k3::tok3n::constant;       \
	using k3::tok3n::defaulted;



#define TOK3N_BEGIN_NAMESPACE_TESTS(...) namespace k3::tok3n::tests __VA_OPT__(::) __VA_ARGS__ { TOK3N_USING_ALL_PARSERS
#define TOK3N_END_NAMESPACE_TESTS(...) }



TOK3N_BEGIN_NAMESPACE_TESTS()

constexpr struct assert_t
{
	friend consteval assert_t operator,(assert_t self, bool b)
	{
		if (!b)
			throw;
		return self;
	}
} assert;



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

TOK3N_END_NAMESPACE_TESTS()
