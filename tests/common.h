#pragma once
#include "samples/adaptor.h"
#include "samples/basic.h"
#include "samples/compound.h"
#include "samples/repeat.h"

TOK3N_BEGIN_NAMESPACE(tests)

namespace traits::basic
{

	template <template <StaticString> class BasicParser>
	struct constructible
	{
		template <char c> static constexpr bool from_char = requires { typename BasicParser<c>; };
		
		template <class Seq> static constexpr bool from_all_chars =
			[]<int... Is>(std::integer_sequence<int, Is...>)
			{
				return (... && from_char<(char)Is>);
			}(Seq{});

		template <class Seq> static constexpr bool from_any_char =
			[]<int... Is>(std::integer_sequence<int, Is...>)
			{
				return (... || from_char<(char)Is>);
			}(Seq{});

		template <StaticString str> static constexpr bool from = requires { typename BasicParser<str>; };
	};

}

namespace traits::compound
{

	template <template <Parser...> class CompoundParser>
	struct constructible
	{
		template <class... Ps>
		static constexpr bool from = requires { typename CompoundParser<Ps...>; };
	};

}

namespace traits::repeat
{

	namespace Exactly
	{
		using k3::tok3n::Exactly;
		struct constructible
		{
			template <Parser P, std::size_t N>
			static constexpr bool from = requires { typename Exactly<P, N>; };
		};
	}

}

namespace traits::operators
{

	template <Parser auto parser>
	concept valid_bang = requires { { !parser } -> Parser; };

	template <Parser auto parser, Modifier auto modifier>
	concept valid_modulo = requires { { parser % modifier } -> Parser; };

	template <Modifier auto modifier, Parser auto... parsers>
	concept valid_function_call = requires { { modifier(parsers...) } -> Parser; };

}

namespace samples::functions
{

	constexpr std::size_t func1(std::vector<std::string_view>&& vec)
	{
		return vec.size();
	}

	constexpr auto func2 = [](const std::optional<std::string_view>& opt) -> std::vector<char>
	{
		if (not opt.has_value())
			return {};
		else
		{
			auto& sv = *opt;
			return { sv.begin(), sv.end() };
		}
	};

	constexpr struct func3_t
	{
		constexpr bool operator()(std::tuple<std::string_view, std::vector<std::string_view>>&& tup) const
		{
			auto&& [sv, vec] = std::move(tup);
			return vec.size() % 2 == 0;
		}
	} func3;

	constexpr struct func3_apply_t
	{
		constexpr bool operator()(std::string_view, std::vector<std::string_view>&& vec) const
		{
			return vec.size() % 2 == 0;
		}
	} func3_apply;

	struct func4
	{
		constexpr func4(int multiply_by)
			: multiply_by(multiply_by) {}

		int multiply_by;

		constexpr std::size_t operator()(const std::tuple<std::vector<std::string_view>, std::optional<std::string_view>>& tup) const
		{
			const auto& [vec, opt] = tup;
			return multiply_by * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
		}
	};

	struct func4_apply
	{
		constexpr func4_apply(int multiply_by)
			: multiply_by(multiply_by) {}

		int multiply_by;

		constexpr std::size_t operator()(const std::vector<std::string_view>& vec, const std::optional<std::string_view>& opt) const
		{
			return multiply_by * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
		}
	};

	constexpr auto sink_func = [](auto&&...) {};

}

namespace samples::classes
{

	class Class1
	{
	public:
		explicit constexpr Class1(int value) : value(value) {}

		explicit constexpr Class1(std::string_view sv)
		{
			if (sv.size() == 1)
			{
				switch (sv.front())
				{
					break; case ' ': value = 0;
					break; case '.': value = 1;
					break; default:  value = 2;
				}
			}
			else
				value = 3;
		}

		friend constexpr bool operator==(const Class1&, const Class1&) = default;

	private:
		int value;
	};

	class Class2
	{
	public:
		explicit constexpr Class2(std::string_view sv1, std::string_view sv2)
			: sv1(sv1), sv2(sv2) {}

		explicit constexpr Class2(const std::tuple<std::string_view, std::string_view>& tup)
		{
			std::tie(sv1, sv2) = tup;
		}

		friend constexpr bool operator==(const Class2&, const Class2&) = default;

	private:
		std::string_view sv1;
		std::string_view sv2;
	};

	class Class3
	{
	public:
		friend constexpr bool operator==(const Class3&, const Class3&) = default;
	};

	class Class4
	{
	public:
		explicit constexpr Class4(const std::tuple<std::string_view, std::string_view>& tup)
		{
			std::tie(sv1, sv2) = tup;
		}

		explicit constexpr operator Class2() const { return Class2{ sv1, sv2 }; }

	private:
		std::string_view sv1;
		std::string_view sv2;
	};

	class Class5
	{
	public:
		explicit constexpr Class5(std::string_view sv1, std::string_view sv2)
			: sv1(sv1), sv2(sv2) {}

		friend constexpr bool operator==(const Class5&, const Class5&) = default;

	private:
		std::string_view sv1;
		std::string_view sv2;
	};

	struct Sink
	{
		constexpr Sink(auto&&...) {};
	};

}

namespace samples::all
{

	using namespace basic;

	using Joi1 = Join<_21>; constexpr Joi1 joi1;
	using Joi2 = Join<_22>; constexpr Joi2 joi2;
	using Joi3 = Join<_23>; constexpr Joi3 joi3;
	using Joi4 = Join<_24>; constexpr Joi4 joi4;
	using Joi5 = Join<_25>; constexpr Joi5 joi5;

	using namespace functions;

	using Tra1 = Transform<_22, func1>;    constexpr Tra1 tra1;
	using Tra2 = Transform<_23, func2>;    constexpr Tra2 tra2;
	using Tra3 = Transform<_24, func3>;    constexpr Tra3 tra3;
	using Tra4 = Transform<_25, func4(3)>; constexpr Tra4 tra4;

	using Apt1 = ApplyTransform<_24, func3_apply>;    constexpr Apt1 apt1;
	using Apt2 = ApplyTransform<_25, func4_apply(3)>; constexpr Apt2 apt2;

	using namespace classes;

	using Int1 = Into<SpaceDot, Class1>;                              constexpr Int1 int1;
	using Int2 = Into<Sequence<ABC, SpaceDot>, Class2>;               constexpr Int2 int2;
	using Int3 = Into<Into<Sequence<ABC, SpaceDot>, Class4>, Class2>; constexpr Int3 int3;

	using Api1 = ApplyInto<Sequence<ABC, SpaceDot>, Class2>; constexpr Api1 api1;
	using Api2 = ApplyInto<Sequence<SpaceDot, ABC>, Class5>; constexpr Api2 api2;

	using Con1 = Constant<_22, 1>;       constexpr Con1 con1;
	using Con2 = Constant<_23, 't'>;     constexpr Con2 con2;
	using Con3 = Constant<_24, true>;    constexpr Con3 con3;
	using Con4 = Constant<_25, nullptr>; constexpr Con4 con4;
	
	using Def1 = Defaulted<_22, int>;    constexpr Def1 def1;
	using Def2 = Defaulted<_23, Class3>; constexpr Def2 def2;

}

TOK3N_END_NAMESPACE(tests)
