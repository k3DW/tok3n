#pragma once
#include <k3/tok3n.h>
#include "samples/basic.h"
#include "samples/classes.h"
#include "samples/functions.h"
#include "framework/parser_list.h"

using Joi1 = Join<_21>; constexpr Joi1 joi1;
using Joi2 = Join<_22>; constexpr Joi2 joi2;
using Joi3 = Join<_23>; constexpr Joi3 joi3;
using Joi4 = Join<_24>; constexpr Joi4 joi4;
using Joi5 = Join<_25>; constexpr Joi5 joi5;

using Tra1 = Transform<_22, Const<func1>>;    constexpr Tra1 tra1;
using Tra2 = Transform<_23, Const<func2>>;    constexpr Tra2 tra2;
using Tra3 = Transform<_24, Const<func3>>;    constexpr Tra3 tra3;
using Tra4 = Transform<_25, Const<func4(3)>>; constexpr Tra4 tra4;

using Apt1 = ApplyTransform<_24, Const<func3_apply>>;    constexpr Apt1 apt1;
using Apt2 = ApplyTransform<_25, Const<func4_apply(3)>>; constexpr Apt2 apt2;

using Int1 = Into<SpaceDot, Class1>;                              constexpr Int1 int1;
using Int2 = Into<Sequence<ABC, SpaceDot>, Class2>;               constexpr Int2 int2;
using Int3 = Into<Into<Sequence<ABC, SpaceDot>, Class4>, Class2>; constexpr Int3 int3;

using Api1 = ApplyInto<Sequence<ABC, SpaceDot>, Class2>; constexpr Api1 api1;
using Api2 = ApplyInto<Sequence<SpaceDot, ABC>, Class5>; constexpr Api2 api2;

using Con1 = Constant<_22, Const<1>>;       constexpr Con1 con1;
using Con2 = Constant<_23, Const<'t'>>;     constexpr Con2 con2;
using Con3 = Constant<_24, Const<true>>;    constexpr Con3 con3;
using Con4 = Constant<_25, Const<nullptr>>; constexpr Con4 con4;
	
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

constexpr auto divergent_list = parser_list(
	joi1, joi2, joi3, joi4, joi5,
	tra1, tra2, tra3, tra4,
	apt1, apt2,
	int1, int2, int3,
	api1, api2,
	con1, con2, con3, con4,
	def1, def2,
	cus1
);

#define DO_TO_SAMPLES_DIVERGENT(F)          \
	F(Joi1) F(Joi2) F(Joi3) F(Joi4) F(Joi5) \
	F(Tra1) F(Tra2) F(Tra3) F(Tra4)         \
	F(Apt1) F(Apt2)                         \
	F(Int1) F(Int2) F(Int3)                 \
	F(Api1) F(Api2)                         \
	F(Con1) F(Con2) F(Con3) F(Con4)         \
	F(Def1) F(Def2)                         \
	F(Cus1)
