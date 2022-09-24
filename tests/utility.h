#pragma once
#include "tok3n/tok3n.h"

BEGIN_NAMESPACE_TOK3N(tests)

constexpr struct assert_t
{
	friend consteval assert_t operator,(assert_t self, bool b)
	{
		if (!b)
			throw;
		return self;
	}
} assert;



template <class T>
static constexpr bool is_parser = Parser<T>;

template <class T>
struct parser_type_of_t
{
	static constexpr bool is_OneChar    = IsOneChar<T>;
	static constexpr bool is_NotChar    = IsNotChar<T>;
	static constexpr bool is_Literal    = IsLiteral<T>;
	static constexpr bool is_Choice     = IsChoice<T>;
	static constexpr bool is_Sequence   = IsSequence<T>;
	static constexpr bool is_OneOrMore  = IsOneOrMore<T>;
	static constexpr bool is_ZeroOrMore = IsZeroOrMore<T>;
	static constexpr bool is_Maybe      = IsMaybe<T>;
	static constexpr bool is_Transform  = IsTransform<T>;
	static constexpr bool is_Flatten    = IsFlatten<T>;
	static constexpr bool is_Ignore     = IsIgnore<T>;
	static constexpr bool is_Delimit    = IsDelimit<T>;
	static constexpr bool is_Custom     = IsCustom<T>;
};

template <class T>
static constexpr parser_type_of_t<T> parser_type_of{};

template <class P>
struct result_of_t
{
	static_assert(requires { typename P::result_type; }, R"(Type used in "result_of" has no type "result_type")");

	template <class R>
	static constexpr bool is = std::same_as<typename P::result_type, R>;
};

template <class T>
static constexpr result_of_t<T> result_of{};



template <Parser P>
struct parse_t
{
	consteval parse_t(Input input) : input(input) {}
	Input input;

	consteval bool success(const typename P::result_type& value, Input remaining) const
	{
		const auto parse_result = P::parse(input);
		const bool parse_success = (parse_result) && (*parse_result == value) && (parse_result.remaining() == remaining);

		const auto lookahead_result = P::lookahead(input);
		const bool lookahead_success = (lookahead_result) && (lookahead_result.remaining() == remaining);

		return parse_success && lookahead_success;
	}

	consteval bool failure(Input remaining) const
	{
		const auto parse_result = P::parse(input);
		const bool parse_failure = (not parse_result) && (parse_result.remaining() == remaining);

		const auto lookahead_result = P::lookahead(input);
		const bool lookahead_failure = (not lookahead_result) && (lookahead_result.remaining() == remaining);

		return parse_failure && lookahead_failure;
	}
};

template <Parser P>
consteval parse_t<P> parse(Input input)
{
	return input;
}



template <Parser P, Parser Q>
consteval bool operator==(P, Q)
{
	return std::is_same_v<P, Q>;
}

END_NAMESPACE_TOK3N(tests)
