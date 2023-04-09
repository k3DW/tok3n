#pragma once
#include <tok3n/tok3n.h>
#include "samples/basic.h"
#include "samples/classes.h"
#include "samples/functions.h"

TOK3N_BEGIN_NAMESPACE(tests::samples::all)

using namespace basic;
using namespace classes;
using namespace functions;

using Joi1 = Join<_21>; constexpr Joi1 joi1;
using Joi2 = Join<_22>; constexpr Joi2 joi2;
using Joi3 = Join<_23>; constexpr Joi3 joi3;
using Joi4 = Join<_24>; constexpr Joi4 joi4;
using Joi5 = Join<_25>; constexpr Joi5 joi5;

using Tra1 = Transform<_22, func1>;    constexpr Tra1 tra1;
using Tra2 = Transform<_23, func2>;    constexpr Tra2 tra2;
using Tra3 = Transform<_24, func3>;    constexpr Tra3 tra3;
using Tra4 = Transform<_25, func4(3)>; constexpr Tra4 tra4;

using Apt1 = ApplyTransform<_24, func3_apply>;    constexpr Apt1 apt1;
using Apt2 = ApplyTransform<_25, func4_apply(3)>; constexpr Apt2 apt2;

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

struct Cus1 : Custom<Cus1>
{
	using result_type = std::size_t;

	static consteval auto get_parser()
	{
		return _25{} % fn<transform>;
	}

	static constexpr std::size_t transform(const std::tuple<std::vector<std::string_view>, std::optional<std::string_view>>& tup)
	{
		const auto& [vec, opt] = tup;
		return 3 * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
	}
};
constexpr Cus1 cus1;

TOK3N_END_NAMESPACE(tests::samples::all)
