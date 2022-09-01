#pragma once
#include <algorithm>
#include <array>
#include <iterator>
#include <optional>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "util/static_string.h"

#include "parsers/parsers.h"

namespace k3::parser
{



	// OneChar
#if 1

	template <static_string str>
		requires (str.unique_and_sorted()) && (str.ascii())
	struct OneChar
	{
		static constexpr Result parse(Input input)
		{
			if (input.empty() || not str.contains(input.front()))
				return Result::failure(input);
			else
			{
				const auto begin = input.begin();
				const auto end = input.end();
				return Result::success({ begin, begin + 1 }, { begin + 1, end });
			}
		}
	};

	namespace detail::choice
	{

		template <static_string lhs, static_string rhs>
		consteval auto onechar_onechar(OneChar<lhs>, OneChar<rhs>)
		{
			constexpr std::size_t count = []() consteval -> std::size_t
			{
				std::string str;
				std::ranges::set_union(rhs, lhs, std::back_inserter(str));
				return str.size();
			}();

			constexpr static_string<count> get_merged = []() consteval -> static_string<count>
			{
				static_string<count> str;
				std::ranges::set_union(rhs, lhs, str.begin());
				return str;
			}();

			return OneChar<get_merged>{};
		}

	}

#endif



	// NotChar
#if 1

	template <static_string str>
		requires (str.unique_and_sorted()) && (str.ascii())
	struct NotChar
	{
		static constexpr Result parse(Input input)
		{
			if (input.empty() || str.contains(input.front()))
				return Result::failure(input);
			else
			{
				const auto begin = input.begin();
				const auto end = input.end();
				return Result::success({ begin, begin + 1 }, { begin + 1, end });
			}
		}
	};

	namespace detail::choice
	{

		template <static_string lhs, static_string rhs>
		consteval auto notchar_notchar(NotChar<lhs>, NotChar<rhs>)
		{
			if constexpr (lhs == rhs)
				return NotChar<lhs>{};
			else
				return OneChar<every_char>{};
		}

		template <static_string lhs, static_string rhs>
		consteval auto onechar_notchar(OneChar<lhs>, NotChar<rhs>)
		{
			if constexpr (lhs == rhs)
				return OneChar<every_char>{};

			else
			{

				constexpr std::size_t count = []() consteval -> std::size_t
				{
					std::string str;
					std::ranges::set_difference(rhs, lhs, std::back_inserter(str));
					return str.size();
				}();

				constexpr static_string<count> get_merged = []() consteval -> static_string<count>
				{
					static_string<count> str;
					std::ranges::set_difference(rhs, lhs, str.begin());
					return str;
				}();

				return NotChar<get_merged>{};

			}
		}

	}

#endif



	// Literal
#if 1

	template <static_string str>
		requires (str.ascii()) && (str.size() > 0)
	struct Literal
	{
		static constexpr Result parse(Input input)
		{
			if (input.empty() || not input.starts_with({ str.begin(), str.end() }))
				return Result::failure(input);
			else
			{
				const auto begin = input.begin();
				const auto end = input.end();
				return Result::success({ begin, begin + str.size() }, { begin + str.size(), end });
			}
		}
	};

	namespace detail::sequence
	{

		template <static_string lhs, static_string rhs>
		consteval auto literal_literal(Literal<lhs>, Literal<rhs>)
		{
			return Literal<lhs + rhs>{};
		}

	}

#endif



	// Choice
#if 1

	namespace detail::choice
	{

		struct Defer
		{
			Input input;
			Result& result_ref;

			template <Parser P>
			constexpr bool operator()(P) const
			{
				Result result = P::parse(input);
				if (result.has_value())
				{
					result_ref = std::move(result);
					return true;
				}
				else
					return false;
			}
		};

	}

	template <Parser... Ps>
		requires (sizeof...(Ps) >= 2)
	struct Choice
	{
		static constexpr Result parse(Input input)
		{
			Result result = Result::failure(input);
			const auto defer = detail::choice::Defer{ .input = input, .result_ref = result };
			(... || defer(Ps{}));

			return result;
		}
	};

	namespace detail::choice
	{

		template <Parser... Ps, Parser... Qs>
		consteval auto choice_choice(Choice<Ps...>, Choice<Qs...>)
		{
			return Choice<Ps..., Qs...>{};
		}

		template <Parser... Ps, Parser P>
		consteval auto choice_parser(Choice<Ps...>, P)
		{
			return Choice<Ps..., P>{};
		}

		template <Parser P, Parser... Ps>
		consteval auto parser_choice(P, Choice<Ps...>)
		{
			return Choice<P, Ps...>{};
		}

	}

#endif



	// Sequence
#if 1

	namespace detail::sequence
	{

		struct Defer
		{
			Input& input;
			std::vector<Result>& results;

			template <Parser P>
			constexpr bool operator()(P) const
			{
				Result result = P::parse(input);
				if (result.has_value())
				{
					input = result.remainder();
					results.emplace_back(std::move(result));
					return true;
				}
				else
					return false;
			}
		};

	}

	template <Parser... Ps>
		requires (sizeof...(Ps) >= 2)
	struct Sequence
	{
		static constexpr Result parse(Input input)
		{
			const Input original_input = input;

			std::vector<Result> results;
			const auto defer = detail::sequence::Defer{ .input = input, .results = results };
			(... && defer(Ps{}));

			if (results.size() == sizeof...(Ps))
				return Result::success(results, input);
			else
				return Result::failure(original_input);
		}
	};

	namespace detail::sequence
	{

		template <Parser... Ps, Parser... Qs>
		consteval auto sequence_sequence(Sequence<Ps...>, Sequence<Qs...>)
		{
			return Sequence<Ps..., Qs...>{};
		}

		template <Parser... Ps, Parser P>
		consteval auto sequence_parser(Sequence<Ps...>, P)
		{
			return Sequence<Ps..., P>{};
		}

		template <Parser P, Parser... Ps>
		consteval auto parser_sequence(P, Sequence<Ps...>)
		{
			return Sequence<P, Ps...>{};
		}

	}

#endif



	// OneOrMore
#if 1

	template <Parser P>
	struct OneOrMore
	{
		static constexpr Result parse(Input input)
		{
			const Input original_input = input;

			std::vector<Result> results;
			while (true)
			{
				Result result = P::parse(input);
				if (result.has_value())
				{
					input = result.remainder();
					results.emplace_back(std::move(result));
					continue;
				}
				else
					break;
			}

			if (results.size() != 0)
				return Result::success(results, input);
			else
				return Result::failure(original_input);
		}
	};

	namespace detail::oneormore
	{

		template <Parser P>
		consteval auto oneormore_zeroorone(ZeroOrOne<P>)
		{
			return ZeroOrMore<P>{};
		}

	}

#endif



	// ZeroOrMore
#if 1

	template <Parser P>
	struct ZeroOrMore
	{
		static constexpr Result parse(Input input)
		{
			const Input original_input = input;

			std::vector<Result> results;
			while (true)
			{
				Result result = P::parse(input);
				if (result.has_value())
				{
					input = result.remainder();
					results.emplace_back(std::move(result));
					continue;
				}
				else
					break;
			}

			return Result::success(results, input);
		}
	};

	namespace detail::zeroormore
	{

		template <Parser P>
		consteval auto zeroormore_oneormore(OneOrMore<P>)
		{
			return ZeroOrMore<P>{};
		}

		template <Parser P>
		consteval auto zeroormore_zeroorone(ZeroOrOne<P>)
		{
			return ZeroOrMore<P>{};
		}

	}

#endif



	// ZeroOrOne
#if 1

	template <Parser P>
	struct ZeroOrOne
	{
		static constexpr Result parse(Input input)
		{
			Result result = P::parse(input);
			if (result.has_value())
				return result;
			else
				return Result::success("", input);
		}
	};

	namespace detail::zeroorone
	{

		template <Parser P>
		consteval auto zeroorone_oneormore(OneOrMore<P>)
		{
			return ZeroOrMore<P>{};
		}

	}

#endif





	template <Parser P1, Parser P2>
	constexpr auto operator|(P1, P2)
	{
		using namespace detail::choice;

		if constexpr (std::same_as<std::remove_cvref_t<P1>, std::remove_cvref_t<P2>>) // (P | P) == P
			return P1{};

		else if constexpr (IsOneChar<P1> && IsOneChar<P2>) // "ab" | "bc" == "abc"
			return onechar_onechar(P1{}, P2{});

		else if constexpr (IsNotChar<P1> && IsNotChar<P2>) // !"a" | !"b" == any_char
			return notchar_notchar(P1{}, P2{});
		else if constexpr (IsOneChar<P1> && IsNotChar<P2>)
			return onechar_notchar(P1{}, P2{});
		else if constexpr (IsNotChar<P1> && IsOneChar<P2>)
			return onechar_notchar(P2{}, P1{});

		else if constexpr (IsChoice<P1> && IsChoice<P2>) // (P1 | P2) | (P3 | P4) == (P1 | P2 | P3 | P4)
			return choice_choice(P1{}, P2{});
		else if constexpr (IsChoice<P1>)                 // (P1 | P2) | P3 == (P1 | P2 | P3)
			return choice_parser(P1{}, P2{});
		else if constexpr (IsChoice<P2>)                 // P1 | (P2 | P3) == (P1 | P2 | P3)
			return parser_choice(P1{}, P2{});

		else
			return Choice<P1, P2>{};
	}

	template <Parser P1, Parser P2>
	constexpr auto operator>>(P1, P2)
	{
		using namespace detail::sequence;

		if constexpr (IsSequence<P1> && IsSequence<P2>) // (P1 >> P2) >> (P3 >> P4) == (P1 >> P2 >> P3 >> P4)
			return sequence_sequence(P1{}, P2{});
		else if constexpr (IsSequence<P1>)              // (P1 >> P2) >> P3 == (P1 >> P2 >> P3)
			return sequence_parser(P1{}, P2{});
		else if constexpr (IsSequence<P2>)              // P1 >> (P2 >> P3) == (P1 >> P2 >> P3)
			return parser_sequence(P1{}, P2{});

		else if constexpr (IsLiteral<P1> && IsLiteral<P2>)
			return literal_literal(P1{}, P2{});

		else
			return Sequence<P1, P2>{};
	}

	template <Parser P>
	constexpr auto operator+(P)
	{
		using namespace detail::oneormore;

		if constexpr (IsOneOrMore<P>)       // +(+P) == +P
			return P{};
		else if constexpr (IsZeroOrMore<P>) // +(*P) == *P
			return P{};
		else if constexpr (IsZeroOrOne<P>)  // +(~P) == *P
			return oneormore_zeroorone(P{});

		else
			return OneOrMore<P>{};
	}

	template <Parser P>
	constexpr auto operator*(P)
	{
		using namespace detail::zeroormore;

		if constexpr (IsOneOrMore<P>)       // *(+P) == *P
			return zeroormore_oneormore(P{});
		else if constexpr (IsZeroOrMore<P>) // *(*P) == *P
			return P{};
		else if constexpr (IsZeroOrOne<P>)  // *(~P) == *P
			return zeroormore_zeroorone(P{});

		else
			return ZeroOrMore<P>{};
	}

	template <Parser P>
	constexpr auto operator~(P)
	{
		using namespace detail::zeroorone;

		if constexpr (IsZeroOrOne<P>)       // ~(~P) == ~P
			return P{};
		else if constexpr (IsOneOrMore<P>)  // ~(+P) == *P
			return zeroorone_oneormore(P{});
		else if constexpr (IsZeroOrMore<P>) // ~(*P) == *P
			return P{};

		else
			return ZeroOrOne<P>{};
	}

	template <static_string str>
	constexpr auto operator!(OneChar<str>)
	{
		return NotChar<str>{};
	}
	template <static_string str>
	constexpr auto operator!(NotChar<str>)
	{
		return OneChar<str>{};
	}










}