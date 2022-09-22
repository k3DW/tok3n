#include "parsers/OneChar.h"
#include "parsers/NotChar.h"
#include "parsers/Literal.h"
#include "operators/ChoiceOp.h"
#include "utility.h"

namespace tests::basic::combine
{

	using k3::parser::OneChar;
	using k3::parser::NotChar;
	using k3::parser::Literal;

	using OC1 = OneChar<"abc">;
	using OC2 = OneChar<"bcd">;
	using OC3 = OneChar<"xyz">;
	using NC1 = NotChar<"abc">;
	using NC2 = NotChar<"bcd">;
	using NC3 = NotChar<"xyz">;

	consteval void choice_onechar()
	{
		constexpr OC1 oc1;
		constexpr OC2 oc2;
		constexpr OC3 oc3;

		static_assert(same(oc1 | oc2, oc2 | oc1));
		static_assert(same(oc1 | oc3, oc3 | oc1));
		static_assert(same(oc2 | oc3, oc3 | oc2));

		static_assert(same<OneChar<"abcd">>(oc1 | oc2));
		static_assert(same<OneChar<"abcxyz">>(oc1 | oc3));
		static_assert(same<OneChar<"bcdxyz">>(oc2 | oc3));
	}
}