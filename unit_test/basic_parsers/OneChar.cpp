#include "parsers/OneChar.h"
#include "utility.h"

namespace OneCharTests
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
		using P_a = OneChar<'a'>;
		using P_b = OneChar<'b'>;
		using P_c = OneChar<'c'>;

		using k3::parser::Parser;
		using k3::parser::IsOneChar;

		static_assert(Parser<P_a> && IsOneChar<P_a>);
		static_assert(Parser<P_b> && IsOneChar<P_b>);
		static_assert(Parser<P_c> && IsOneChar<P_c>);

		static_assert(is_result_of<P_a, std::string_view>);
		static_assert(is_result_of<P_b, std::string_view>);
		static_assert(is_result_of<P_c, std::string_view>);

		constexpr P_a p_a;
		constexpr P_b p_b;
		constexpr P_c p_c;

		{
			constexpr auto a1 = P_a::parse("a");
			constexpr auto a2 = p_a.parse("a");
			static_assert(check_result(a1, "a", ""));
			static_assert(check_result(a2, "a", ""));
		}

		{
			constexpr auto b1 = P_b::parse("ba");
			constexpr auto b2 = p_b.parse("ba");
			static_assert(check_result(b1, "b", "a"));
			static_assert(check_result(b2, "b", "a"));
		}

		{
			constexpr auto c1 = P_c::parse("cba");
			constexpr auto c2 = p_c.parse("cba");
			static_assert(check_result(c1, "c", "ba"));
			static_assert(check_result(c2, "c", "ba"));
		}
	}

	consteval void multiple_chars()
	{
		using P_abc = OneChar<"abc">;
		using k3::parser::Parser;
		using k3::parser::IsOneChar;

		static_assert(Parser<P_abc> && IsOneChar<P_abc>);
		static_assert(is_result_of<P_abc, std::string_view>);

		constexpr P_abc p_abc;

		constexpr auto abc1 = P_abc::parse("abc");
		constexpr auto abc2 = P_abc::parse("acb");
		constexpr auto abc3 = P_abc::parse("bac");
		constexpr auto abc4 = P_abc::parse("bca");
		constexpr auto abc5 = P_abc::parse("cab");
		constexpr auto abc6 = P_abc::parse("cba");
		static_assert(check_result(abc1, "a", "bc"));
		static_assert(check_result(abc2, "a", "cb"));
		static_assert(check_result(abc3, "b", "ac"));
		static_assert(check_result(abc4, "b", "ca"));
		static_assert(check_result(abc5, "c", "ab"));
		static_assert(check_result(abc6, "c", "ba"));
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

}
