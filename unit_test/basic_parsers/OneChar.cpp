#include "parsers/OneChar.h"
#include "utility.h"

namespace tests::basic::OneChar
{

	using k3::parser::OneChar;

	template <char... c>
	concept Constructible_From_All_Chars = (... && requires { typename OneChar<c>; });

	template <char... c>
	concept Constructible_From_Any_Chars = (... || requires { typename OneChar<c>; });

	template <k3::static_string str>
	concept Constructible_From_String = requires { typename OneChar<str>; };

	consteval void single_char()
	{
		using P = OneChar<'a'>;

		static_assert(k3::parser::Parser<P>);
		static_assert(k3::parser::IsOneChar<P>);
		static_assert(is_result_of<P, std::string_view>);

		constexpr P p;

		constexpr auto r1 = P::parse("ab");
		constexpr auto r2 = p.parse("ab");
		static_assert(validate(success, r1, "a", "b"));
		static_assert(validate(success, r2, "a", "b"));

		constexpr auto r3 = P::parse("ba");
		constexpr auto r4 = p.parse("ba");
		static_assert(validate(failure, r3, "ba"));
		static_assert(validate(failure, r4, "ba"));
	}

	consteval void multiple_chars()
	{
		using P = OneChar<"abc">;

		static_assert(k3::parser::Parser<P>);
		static_assert(k3::parser::IsOneChar<P>);
		static_assert(is_result_of<P, std::string_view>);

		constexpr P p;

		constexpr auto r1 = P::parse("abc");
		constexpr auto r2 = P::parse("acb");
		constexpr auto r3 = P::parse("bac");
		constexpr auto r4 = P::parse("bca");
		constexpr auto r5 = P::parse("cab");
		constexpr auto r6 = P::parse("cba");
		static_assert(validate(success, r1, "a", "bc"));
		static_assert(validate(success, r2, "a", "cb"));
		static_assert(validate(success, r3, "b", "ac"));
		static_assert(validate(success, r4, "b", "ca"));
		static_assert(validate(success, r5, "c", "ab"));
		static_assert(validate(success, r6, "c", "ba"));
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
		using P = OneChar<'a'>;

		constexpr auto r1 = P::lookahead("ab");
		static_assert(validate(success, r1, "b"));
		constexpr auto r2 = P::lookahead("ba");
		static_assert(validate(failure, r2, "ba"));
	}

	consteval void lookahead_multiple_chars()
	{
		using P = OneChar<"abc">;

		constexpr auto r1 = P::lookahead("abc");
		static_assert(validate(success, r1, "bc"));
		constexpr auto r2 = P::lookahead("bac");
		static_assert(validate(success, r2, "ac"));
		constexpr auto r3 = P::lookahead(" bac");
		static_assert(validate(failure, r3, " bac"));
	}

}
