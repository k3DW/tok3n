#include "parsers/OneChar.h"

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
concept OneChar_Constructible_From_All_Chars = (... && requires { typename NewOneChar<c>; });

template <char... c>
concept OneChar_Constructible_From_Any_Chars = (... || requires { typename NewOneChar<c>; });

template <static_string str>
concept OneChar_Constructible_String = requires { typename NewOneChar<str>; };

void test_OneChar()
{
	using P_a = NewOneChar<'a'>;
	using P_b = NewOneChar<'b'>;
	using P_c = NewOneChar<'c'>;
	using P_abc = NewOneChar<"abc">;

	constexpr P_a p_a;
	constexpr P_b p_b;
	constexpr P_c p_c;
	constexpr P_abc p_abc;
	//constexpr auto p_abc2 = p_a | p_b | p_c;

	static_assert(same_as<P_abc>(p_abc));
	//static_assert(same_as<P_abc>(p_abc2));
	//static_assert(same_as(p_abc, p_abc2));

	constexpr NewResult<std::string_view> a1 = P_a::parse("a");
	constexpr NewResult<std::string_view> a2 = p_a.parse("a");

	static_assert(a1.has_value());
	static_assert(a1.value() == "a");
	static_assert(a1.remaining() == "");
	static_assert(a2.has_value());
	static_assert(a2.value() == "a");
	static_assert(a2.remaining() == "");

	constexpr NewResult<std::string_view> b1 = P_b::parse("ba");
	constexpr NewResult<std::string_view> b2 = p_b.parse("ba");

	static_assert(b1.has_value());
	static_assert(b1.value() == "b");
	static_assert(b1.remaining() == "a");
	static_assert(b2.has_value());
	static_assert(b2.value() == "b");
	static_assert(b2.remaining() == "a");

	constexpr NewResult<std::string_view> c1 = P_c::parse("cba");
	constexpr NewResult<std::string_view> c2 = p_c.parse("cba");

	static_assert(c1.has_value());
	static_assert(c1.value() == "c");
	static_assert(c1.remaining() == "ba");
	static_assert(c2.has_value());
	static_assert(c2.value() == "c");
	static_assert(c2.remaining() == "ba");

	constexpr NewResult<std::string_view> abc1 = P_abc::parse("abc");
	constexpr NewResult<std::string_view> abc2 = P_abc::parse("acb");
	constexpr NewResult<std::string_view> abc3 = P_abc::parse("bac");
	constexpr NewResult<std::string_view> abc4 = P_abc::parse("bca");
	constexpr NewResult<std::string_view> abc5 = P_abc::parse("cab");
	constexpr NewResult<std::string_view> abc6 = P_abc::parse("cba");

	static_assert(abc1.has_value());
	static_assert(abc2.has_value());
	static_assert(abc3.has_value());
	static_assert(abc4.has_value());
	static_assert(abc5.has_value());
	static_assert(abc6.has_value());

	static_assert(abc1.value() == "a");
	static_assert(abc2.value() == "a");
	static_assert(abc3.value() == "b");
	static_assert(abc4.value() == "b");
	static_assert(abc5.value() == "c");
	static_assert(abc6.value() == "c");

	static_assert(abc1.remaining() == "bc");
	static_assert(abc2.remaining() == "cb");
	static_assert(abc3.remaining() == "ac");
	static_assert(abc4.remaining() == "ca");
	static_assert(abc5.remaining() == "ab");
	static_assert(abc6.remaining() == "ba");

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
