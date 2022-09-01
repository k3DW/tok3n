#include "parser.h"

using namespace k3;
using namespace k3::parser;

template <class P>
consteval bool same_as(auto&& rhs)
{
	return std::same_as<P, std::remove_cvref_t<decltype(rhs)>>;
}

consteval bool same_as(auto&& lhs, auto&& rhs)
{
	return std::same_as<std::remove_cvref_t<decltype(lhs)>, std::remove_cvref_t<decltype(rhs)>>;
}

template <char... c>
concept OneChar_Constructible_From_All_Chars = (... && requires { typename OneChar<c>; });

template <char... c>
concept OneChar_Constructible_From_Any_Chars = (... || requires { typename OneChar<c>; });

template <static_string str>
concept OneChar_Constructible_String = requires { typename OneChar<str>; };

void test_OneChar()
{
	using P_a = OneChar<'a'>;
	using P_b = OneChar<'b'>;
	using P_c = OneChar<'c'>;
	using P_abc = OneChar<"abc">;

	constexpr P_a p_a;
	constexpr P_b p_b;
	constexpr P_c p_c;
	constexpr P_abc p_abc;
	constexpr auto p_abc2 = p_a | p_b | p_c;

	static_assert(same_as<P_abc>(p_abc));
	static_assert(same_as<P_abc>(p_abc2));
	static_assert(same_as(p_abc, p_abc2));

	constexpr Result a1 = P_a::parse("a");
	constexpr Result a2 = p_a.parse("a");

	static_assert(a1.holds_string_view());
	static_assert(a1.get_string_view() == "a");
	static_assert(a1.flatten() == "a");
	static_assert(a1.remainder() == "");
	static_assert(a2.holds_string_view());
	static_assert(a2.get_string_view() == "a");
	static_assert(a2.flatten() == "a");
	static_assert(a2.remainder() == "");

	constexpr Result b1 = P_b::parse("ba");
	constexpr Result b2 = p_b.parse("ba");

	static_assert(b1.holds_string_view());
	static_assert(b1.get_string_view() == "b");
	static_assert(b1.flatten() == "b");
	static_assert(b1.remainder() == "a");
	static_assert(b2.holds_string_view());
	static_assert(b2.get_string_view() == "b");
	static_assert(b2.flatten() == "b");
	static_assert(b2.remainder() == "a");

	constexpr Result c1 = P_c::parse("cba");
	constexpr Result c2 = p_c.parse("cba");

	static_assert(c1.holds_string_view());
	static_assert(c1.get_string_view() == "c");
	static_assert(c1.flatten() == "c");
	static_assert(c1.remainder() == "ba");
	static_assert(c2.holds_string_view());
	static_assert(c2.get_string_view() == "c");
	static_assert(c2.flatten() == "c");
	static_assert(c2.remainder() == "ba");

	constexpr Result abc1 = P_abc::parse("abc");
	constexpr Result abc2 = P_abc::parse("acb");
	constexpr Result abc3 = P_abc::parse("bac");
	constexpr Result abc4 = P_abc::parse("bca");
	constexpr Result abc5 = P_abc::parse("cab");
	constexpr Result abc6 = P_abc::parse("cba");

	static_assert(abc1.holds_string_view());
	static_assert(abc2.holds_string_view());
	static_assert(abc3.holds_string_view());
	static_assert(abc4.holds_string_view());
	static_assert(abc5.holds_string_view());
	static_assert(abc6.holds_string_view());

	static_assert(abc1.get_string_view() == "a");
	static_assert(abc2.get_string_view() == "a");
	static_assert(abc3.get_string_view() == "b");
	static_assert(abc4.get_string_view() == "b");
	static_assert(abc5.get_string_view() == "c");
	static_assert(abc6.get_string_view() == "c");

	static_assert(abc1.remainder() == "bc");
	static_assert(abc2.remainder() == "cb");
	static_assert(abc3.remainder() == "ac");
	static_assert(abc4.remainder() == "ca");
	static_assert(abc5.remainder() == "ab");
	static_assert(abc6.remainder() == "ba");

	static_assert(OneChar_Constructible_From_All_Chars<
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
	static_assert(not OneChar_Constructible_From_Any_Chars<
		128, 129,
		130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
		140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
		150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
		160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
		170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
		180, 181, 182, 183, 184, 185, 186, 187, 188, 189,
		190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
		200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
		210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
		220, 221, 222, 223, 224, 225, 226, 227, 228, 229,
		230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
		240, 241, 242, 243, 244, 245, 246, 247, 248, 249,
		250, 251, 252, 253, 254, 255>
	);

	static_assert(OneChar_Constructible_String<"abc">);
	static_assert(not OneChar_Constructible_String<"acb">);
	static_assert(not OneChar_Constructible_String<"bac">);
	static_assert(not OneChar_Constructible_String<"bca">);
	static_assert(not OneChar_Constructible_String<"cab">);
	static_assert(not OneChar_Constructible_String<"cba">);
}