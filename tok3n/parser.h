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

namespace k3::parser
{



	// static_string
#if 1

	template <std::size_t N>
	struct static_string
	{
		std::array<char, N> data = {};

		constexpr static_string() = default;

		constexpr static_string(const char(&input)[N + 1]) noexcept
		{
			for (std::size_t i = 0; i < N; i++)
				data[i] = input[i];
		}

		constexpr static_string(char c) noexcept requires (N == 1)
		{
			data[0] = c;
		}

		constexpr bool contains(char c) const noexcept
		{
			return std::string_view(data.data(), N).contains(c);
		}

		constexpr auto begin() const { return data.begin(); }
		constexpr auto begin() { return data.begin(); }
		constexpr auto end()   const { return data.end(); }
		constexpr auto end() { return data.end(); }

		constexpr std::size_t size() const noexcept { return N; }

		constexpr bool ascii() const { return std::ranges::all_of(data, [](char c) -> bool { return (c & 0x80) == 0; }); }

		constexpr bool unique_and_sorted() const
		{
			if constexpr (N == 1)
				return true;
			else
			{
				for (std::size_t i = 1; i < N; i++)
					if (data[i - 1] >= data[i])
						return false;
				return true;
			}
		}
	};

	template <std::size_t N>
	static_string(const char(&)[N])->static_string<N - 1>;

	static_string(char)->static_string<1>;

	template <std::size_t M, std::size_t N>
	constexpr bool operator==(const static_string<M>& lhs, const static_string<N>& rhs)
	{
		if constexpr (M != N)
			return false;
		else
			return lhs.data == rhs.data;
	}

	template <std::size_t M, std::size_t N>
	constexpr static_string<M + N> operator+(const static_string<M>& lhs, const static_string<N>& rhs)
	{
		static_string<M + N> str;
		std::ranges::copy(lhs, str.begin());
		std::ranges::copy(rhs, str.begin() + M);
		return str;
	}

	constexpr static_string every_char = []() consteval -> static_string<128>
	{
		static_string<128> str;
		for (int c = 0; c < 128; c++)
			str.data[c] = c;
		return str;
	}();

	template <static_string str>
	constexpr auto every_char_except = []()
	{
		static_string<128 - str.size()> output;
		auto it = output.data.begin();

		std::string_view sv = { str.begin(), str.end() };
		for (int c = 0; c < 128; c++)
		{
			if (not sv.contains(c))
				*it++ = c;
		}

		return output;
	}();

	template <std::size_t N>
		requires (N > 0 && N < 128)
	constexpr static_string<128 - N> inverse_string(const static_string<N>& str)
	{
		static_string<128 - N> output;
		auto it = output.data.begin();

		std::string_view sv = { str.begin(), str.end() };
		for (int c = 0; c < 128; c++)
		{
			if (not sv.contains(c))
				*it++ = c;
		}

		return output;
	}

#endif



	// Declarations
#if 1

	enum class ParserType
	{
		None,
		OneChar,
		NotChar,
		Literal,
		Choice,
		Sequence,
		OneOrMore,
		ZeroOrMore,
		ZeroOrOne,
	};

	template <class P>
	constexpr ParserType parser_type_v = ParserType::None;

	template <class P> concept IsOneChar = parser_type_v<P> == ParserType::OneChar;
	template <class P> concept IsNotChar = parser_type_v<P> == ParserType::NotChar;
	template <class P> concept IsLiteral = parser_type_v<P> == ParserType::Literal;
	template <class P> concept IsChoice = parser_type_v<P> == ParserType::Choice;
	template <class P> concept IsSequence = parser_type_v<P> == ParserType::Sequence;
	template <class P> concept IsOneOrMore = parser_type_v<P> == ParserType::OneOrMore;
	template <class P> concept IsZeroOrMore = parser_type_v<P> == ParserType::ZeroOrMore;
	template <class P> concept IsZeroOrOne = parser_type_v<P> == ParserType::ZeroOrOne;

	using Input = std::string_view;
	class Result;

	template <class P>
	concept Parser =
		(parser_type_v<P> != ParserType::None) &&
		(sizeof(P) == 1) &&
		requires (Input input)
	{
		{ P::parse(input) } -> std::same_as<Result>;
	};


	template <static_string str>
		requires (str.unique_and_sorted()) && (str.ascii())
	struct OneChar;

	template <static_string str>
	constexpr ParserType parser_type_v<OneChar<str>> = ParserType::OneChar;


	template <static_string str>
		requires (str.unique_and_sorted()) && (str.ascii())
	struct NotChar;

	template <static_string str>
	constexpr ParserType parser_type_v<NotChar<str>> = ParserType::NotChar;


	template <static_string str>
		requires (str.ascii()) && (str.size() > 0)
	struct Literal;

	template <static_string str>
	constexpr ParserType parser_type_v<Literal<str>> = ParserType::Literal;


	template <Parser... Ps>
		requires (sizeof...(Ps) >= 2)
	struct Choice;

	template <Parser... Ps>
	constexpr ParserType parser_type_v<Choice<Ps...>> = ParserType::Choice;


	template <Parser... Ps>
		requires (sizeof...(Ps) >= 2)
	struct Sequence;

	template <Parser... Ps>
	constexpr ParserType parser_type_v<Sequence<Ps...>> = ParserType::Sequence;


	template <Parser P>
	struct OneOrMore;

	template <Parser P>
	constexpr ParserType parser_type_v<OneOrMore<P>> = ParserType::OneOrMore;


	template <Parser P>
	struct ZeroOrMore;

	template <Parser P>
	constexpr ParserType parser_type_v<ZeroOrMore<P>> = ParserType::ZeroOrMore;


	template <Parser P>
	struct ZeroOrOne;

	template <Parser P>
	constexpr ParserType parser_type_v<ZeroOrOne<P>> = ParserType::ZeroOrOne;

#endif



	// Result
#if 1

	class Result
	{
	public:
		static constexpr Result failure(std::string_view remaining)
		{
			return Result(std::monostate{}, remaining);
		}

		static constexpr Result success(std::string_view result, std::string_view remaining)
		{
			return Result(result, remaining);
		}

		static constexpr Result success(std::vector<Result>& results, std::string_view remaining)
		{
			return Result(std::move(results), remaining);
		}

		constexpr bool empty()     const noexcept { return std::holds_alternative<std::monostate>(result); }
		constexpr bool has_value() const noexcept { return not std::holds_alternative<std::monostate>(result); }
		constexpr operator bool()  const noexcept { return not std::holds_alternative<std::monostate>(result); }

		constexpr bool holds_string_view() const noexcept { return std::holds_alternative<std::string_view>(result); }
		constexpr auto get_string_view()   const { return std::get<std::string_view>(result); }

		constexpr bool  holds_vector() const noexcept { return std::holds_alternative<std::vector<Result>>(result); }
		constexpr auto& get_vector()   const { return std::get<std::vector<Result>>(result); }

		constexpr std::string_view remainder() const noexcept { return remaining; }

		constexpr const char* begin() const noexcept;
		constexpr const char* end()   const noexcept;

		constexpr std::string_view flatten() const noexcept { return std::string_view{ begin(), end() }; }

	private:
		Result() = delete;

		template <class T>
		constexpr Result(T&& result, std::string_view remaining) : result(std::forward<T>(result)), remaining(remaining) {}

		using variant = std::variant<std::monostate, std::string_view, std::vector<Result>>;

		variant          result;
		std::string_view remaining;
	};

	constexpr const char* Result::begin() const noexcept
	{
		if (holds_string_view())
			return get_string_view().data();
		else if (holds_vector())
		{
			const auto& vector = get_vector();
			for (auto it = vector.begin(); it != vector.end(); it++)
			{
				const char* begin = it->begin();
				if (begin != nullptr)
					return begin;
			}
		}

		return nullptr;
	}

	constexpr const char* Result::end() const noexcept
	{
		if (holds_string_view())
		{
			auto sv = get_string_view();
			return sv.data() + sv.size();
		}
		else if (holds_vector())
		{
			const auto& vector = get_vector();
			for (auto it = vector.rbegin(); it != vector.rend(); it++)
			{
				const char* begin = it->end();
				if (begin != nullptr)
					return begin;
			}
		}

		return nullptr;
	}

#endif



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