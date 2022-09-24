#pragma once
#include <concepts>
#include <type_traits>

#include "parsers/parsers.h"
#include "operators/operators.h"

using k3::parser::Input;
using k3::parser::Result;
using k3::parser::failure;
using k3::parser::success;



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
consteval bool validate(k3::parser::success_t, const Result<T>& result, const std::type_identity_t<T>& t, std::string_view remaining)
{
	return (result) && (*result == t) && (result.remaining() == remaining);
}

consteval bool validate(k3::parser::success_t, const Result<void>& result, std::string_view remaining)
{
	return (result) && (result.remaining() == remaining);
}

template <class T>
consteval bool validate(k3::parser::failure_t, const Result<T>& result, std::string_view remaining)
{
	return (!result) && (result.remaining() == remaining);
}

template <class P, class R>
concept is_result_of = std::same_as<typename P::result_type, R>;



namespace k3::tok3n::tests
{

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
	static constexpr bool is_parser = k3::parser::Parser<T>;

	template <class T>
	struct parser_type_of_t
	{
		static constexpr bool is_OneChar    = k3::parser::IsOneChar<T>;
		static constexpr bool is_NotChar    = k3::parser::IsNotChar<T>;
		static constexpr bool is_Literal    = k3::parser::IsLiteral<T>;
		static constexpr bool is_Choice     = k3::parser::IsChoice<T>;
		static constexpr bool is_Sequence   = k3::parser::IsSequence<T>;
		static constexpr bool is_OneOrMore  = k3::parser::IsOneOrMore<T>;
		static constexpr bool is_ZeroOrMore = k3::parser::IsZeroOrMore<T>;
		static constexpr bool is_ZeroOrOne  = k3::parser::IsZeroOrOne<T>;
		static constexpr bool is_Transform  = k3::parser::IsTransform<T>;
		static constexpr bool is_Flatten    = k3::parser::IsFlatten<T>;
		static constexpr bool is_Ignore     = k3::parser::IsIgnore<T>;
		static constexpr bool is_Delimit    = k3::parser::IsDelimit<T>;
		static constexpr bool is_Custom     = k3::parser::IsCustom<T>;
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



	template <k3::parser::Parser P>
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

	template <k3::parser::Parser P>
	consteval parse_t<P> parse(Input input)
	{
		return input;
	}

}
