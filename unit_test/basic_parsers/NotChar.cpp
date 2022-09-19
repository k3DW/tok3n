#include "parsers/NotChar.h"
#include "utility.h"

namespace NotCharTests
{

	using k3::parser::NotChar;

	template <char... c>
	concept Constructible_From_All_Chars = (... && requires { typename NotChar<c>; });

	template <char... c>
	concept Constructible_From_Any_Chars = (... || requires { typename NotChar<c>; });

	template <k3::static_string str>
	concept Constructible_From_String = requires { typename NotChar<str>; };

	consteval void single_char()
	{
		using P = NotChar<'a'>;

		static_assert(k3::parser::Parser<P>);
		static_assert(k3::parser::IsNotChar<P>);
		static_assert(is_result_of<P, std::string_view>);

		constexpr P p;

		constexpr auto r1 = P::parse("ab");
		constexpr auto r2 = p.parse("ab");
		static_assert(validate(failure, r1, "ab"));
		static_assert(validate(failure, r2, "ab"));

		constexpr auto r3 = P::parse("ba");
		constexpr auto r4 = p.parse("ba");
		static_assert(validate(success, r3, "b", "a"));
		static_assert(validate(success, r4, "b", "a"));
	}

	consteval void multiple_chars()
	{
		using P = NotChar<"abc">;

		static_assert(k3::parser::Parser<P>);
		static_assert(k3::parser::IsNotChar<P>);
		static_assert(is_result_of<P, std::string_view>);

		constexpr P p;

		constexpr auto r1 = P::parse("a");
		constexpr auto r2 = p.parse("a");
		constexpr auto r3 = P::parse("ba");
		constexpr auto r4 = p.parse("ba");
		constexpr auto r5 = P::parse("cba");
		constexpr auto r6 = p.parse("cba");
		static_assert(validate(failure, r1, "a"));
		static_assert(validate(failure, r2, "a"));
		static_assert(validate(failure, r3, "ba"));
		static_assert(validate(failure, r4, "ba"));
		static_assert(validate(failure, r5, "cba"));
		static_assert(validate(failure, r6, "cba"));

		constexpr auto r7 = P::parse("dcba");
		constexpr auto r8 = p.parse("dcba");
		constexpr auto r9 = P::parse("edcba");
		constexpr auto r10 = p.parse("edcba");
		static_assert(validate(success, r7, "d", "cba"));
		static_assert(validate(success, r8, "d", "cba"));
		static_assert(validate(success, r9, "e", "dcba"));
		static_assert(validate(success, r10, "e", "dcba"));
	}

	consteval void constructible_from_ascii_only()
	{
		static_assert(Constructible_From_All_Chars<
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
			30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
			40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
			50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
			60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
			70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
			80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
			90, 91, 92, 93, 94, 95, 96, 97, 98, 99,
			100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
			110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
			120, 121, 122, 123, 124, 125, 126, 127>
		);

		static_assert(not Constructible_From_Any_Chars<
			-1, -2, -3, -4, -5, -6, -7, -8, -9,
			-10, -11, -12, -13, -14, -15, -16, -17, -18, -19,
			-20, -21, -22, -23, -24, -25, -26, -27, -28, -29,
			-30, -31, -32, -33, -34, -35, -36, -37, -38, -39,
			-40, -41, -42, -43, -44, -45, -46, -47, -48, -49,
			-50, -51, -52, -53, -54, -55, -56, -57, -58, -59,
			-60, -61, -62, -63, -64, -65, -66, -67, -68, -69,
			-70, -71, -72, -73, -74, -75, -76, -77, -78, -79,
			-80, -81, -82, -83, -84, -85, -86, -87, -88, -89,
			-90, -91, -92, -93, -94, -95, -96, -97, -98, -99,
			-100, -101, -102, -103, -104, -105, -106, -107, -108, -109,
			-110, -111, -112, -113, -114, -115, -116, -117, -118, -119,
			-120, -121, -122, -123, -124, -125, -126, -127, -128>
		);
	}

	consteval void constructible_alphabetically_only()
	{
		static_assert(Constructible_From_String<"abc">);
		static_assert(not Constructible_From_String<"acb">);
		static_assert(not Constructible_From_String<"bac">);
		static_assert(not Constructible_From_String<"bca">);
		static_assert(not Constructible_From_String<"cab">);
		static_assert(not Constructible_From_String<"cba">);
	}

	consteval void ensure_non_empty()
	{
		static_assert(not Constructible_From_String<"">);
	}

	consteval void lookahead_single_char()
	{
		using P = NotChar<'a'>;

		constexpr auto r1 = P::lookahead("ba");
		static_assert(validate(success, r1, "a"));
		constexpr auto r2 = P::lookahead("ab");
		static_assert(validate(failure, r2, "ab"));
	}

	consteval void lookahead_multiple_chars()
	{
		using P = NotChar<"abc">;

		constexpr auto r1 = P::lookahead("a");
		static_assert(validate(failure, r1, "a"));
		constexpr auto r2 = P::lookahead("ba");
		static_assert(validate(failure, r2, "ba"));
		constexpr auto r3 = P::lookahead("dcba");
		static_assert(validate(success, r3, "cba"));
		constexpr auto r4 = P::lookahead(" dcba");
		static_assert(validate(success, r4, "dcba"));
	}

}
