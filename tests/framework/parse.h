#pragma once
#include <k3/tok3n/concepts/Parser.h>
#include <source_location>

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

struct TestRunner
{
	struct Error
	{
		std::string_view message;
		std::source_location location;
	};

	static inline std::vector<Error> all_errors;
	static inline std::size_t total_assertions;
};

inline void Assert(bool condition, std::string_view message, std::source_location location = std::source_location::current())
{
	++TestRunner::total_assertions;

	if (not condition)
		TestRunner::all_errors.emplace_back(message, std::move(location));
}

#define TOK3N_STATIC_ASSERT_DISABLED

#ifdef TOK3N_STATIC_ASSERT_DISABLED
#define TOK3N_STATIC_ASSERT(...) static_assert(true)
#else
#define TOK3N_STATIC_ASSERT(...) static_assert(...)
#endif

#define TOK3N_ASSERT(CONDITION, MESSAGE)         \
	TOK3N_STATIC_ASSERT((CONDITION), (MESSAGE)); \
	Assert((CONDITION), (MESSAGE))

#define TOK3N_ASSERT_PARSER_CONCEPT(P)                   \
	TOK3N_ASSERT(Parser<P>,                              \
		"(" #P ") does not satisfy the Parser concept.")

#define TOK3N_ASSERT_PARSE_VALID(P, INPUT)                                           \
	TOK3N_ASSERT((P::parse(INPUT)).has_value(),                                      \
		"(" #P "::parse(" #INPUT ")) does not give a valid result, but it should." )

#define TOK3N_ASSERT_PARSE_INVALID(P, INPUT)                                     \
	TOK3N_ASSERT(not (P::parse(INPUT)).has_value(),                              \
		"(" #P "::parse(" #INPUT ")) gives a valid result, but it should not." )

#define TOK3N_ASSERT_PARSE_RESULT(P, INPUT, OUTPUT)                  \
	TOK3N_ASSERT(*(P::parse(INPUT)) == (OUTPUT),                     \
		"*(" #P "::parse(" #INPUT ")) does not equal (" #OUTPUT ")")

#define TOK3N_ASSERT_PARSE_REMAINING(P, INPUT, REMAINING)                          \
	TOK3N_ASSERT((P::parse(INPUT)).remaining() == (REMAINING),                     \
		"(" #P "::parse(" #INPUT ")).remaining() does not equal (" #REMAINING ")")

#define TOK3N_ASSERT_LOOKAHEAD_VALID(P, INPUT)                                           \
	TOK3N_ASSERT((P::lookahead(INPUT)).has_value(),                                      \
		"(" #P "::lookahead(" #INPUT ")) does not give a valid result, but it should." )

#define TOK3N_ASSERT_LOOKAHEAD_INVALID(P, INPUT)                                     \
	TOK3N_ASSERT(not (P::lookahead(INPUT)).has_value(),                              \
		"(" #P "::lookahead(" #INPUT ")) gives a valid result, but it should not." )

#define TOK3N_ASSERT_LOOKAHEAD_REMAINING(P, INPUT, REMAINING)                          \
	TOK3N_ASSERT((P::lookahead(INPUT)).remaining() == (REMAINING),                     \
		"(" #P "::lookahead(" #INPUT ")).remaining() does not equal (" #REMAINING ")")

#define TOK3N_ASSERT_SUCCESS(P, INPUT, OUTPUT, REMAINING)      \
	do {                                                       \
		TOK3N_ASSERT_PARSER_CONCEPT(P);                        \
		TOK3N_ASSERT_PARSE_VALID(P, INPUT);                    \
		TOK3N_ASSERT_PARSE_RESULT(P, INPUT, OUTPUT);           \
		TOK3N_ASSERT_PARSE_REMAINING(P, INPUT, REMAINING);     \
		TOK3N_ASSERT_LOOKAHEAD_VALID(P, INPUT);                \
		TOK3N_ASSERT_LOOKAHEAD_REMAINING(P, INPUT, REMAINING); \
	} while (false)

#define TOK3N_ASSERT_SUCCESS_VOID(P, INPUT, REMAINING)         \
	do {                                                       \
		TOK3N_ASSERT_PARSER_CONCEPT(P);                        \
		TOK3N_ASSERT_PARSE_VALID(P, INPUT);                    \
		TOK3N_ASSERT_PARSE_REMAINING(P, INPUT, REMAINING);     \
		TOK3N_ASSERT_LOOKAHEAD_VALID(P, INPUT);                \
		TOK3N_ASSERT_LOOKAHEAD_REMAINING(P, INPUT, REMAINING); \
	} while (false)

#define TOK3N_ASSERT_FAILURE(P, INPUT)                     \
	do {                                                   \
		TOK3N_ASSERT_PARSER_CONCEPT(P);                    \
		TOK3N_ASSERT_PARSE_INVALID(P, INPUT);              \
		TOK3N_ASSERT_PARSE_REMAINING(P, INPUT, INPUT);     \
		TOK3N_ASSERT_LOOKAHEAD_INVALID(P, INPUT);          \
		TOK3N_ASSERT_LOOKAHEAD_REMAINING(P, INPUT, INPUT); \
	} while (false)

#define TOK3N_ASSERT_LOOKAHEAD_ONLY(P, INPUT, REMAINING)       \
	do {                                                       \
		TOK3N_ASSERT_PARSER_CONCEPT(P);                        \
		TOK3N_ASSERT_PARSE_INVALID(P, INPUT);                  \
		TOK3N_ASSERT_PARSE_REMAINING(P, INPUT, INPUT);         \
		TOK3N_ASSERT_LOOKAHEAD_VALID(P, INPUT);                \
		TOK3N_ASSERT_LOOKAHEAD_REMAINING(P, INPUT, REMAINING); \
	} while (false)
