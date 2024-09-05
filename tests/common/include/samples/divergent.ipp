using Joi1 = Join<_21>; constexpr Joi1 joi1;
using Joi2 = Join<_22>; constexpr Joi2 joi2;
using Joi3 = Join<_23>; constexpr Joi3 joi3;
using Joi4 = Join<_24>; constexpr Joi4 joi4;
using Joi5 = Join<_25>; constexpr Joi5 joi5;

using Map1 = Map<_22, Const<func1>>;    constexpr Map1 tra1;
using Map2 = Map<_23, Const<func2>>;    constexpr Map2 tra2;
using Map3 = Map<_24, Const<func3>>;    constexpr Map3 tra3;
using Map4 = Map<_25, Const<func4(3)>>; constexpr Map4 tra4;

using Apt1 = ApplyTransform<_24, Const<func3_apply>>;    constexpr Apt1 apt1;
using Apt2 = ApplyTransform<_25, Const<func4_apply(3)>>; constexpr Apt2 apt2;

using Int1 = aliases::Into<SpaceDot, Class1>;                                       constexpr Int1 int1;
using Int2 = aliases::Into<Sequence<ABC, SpaceDot>, Class2>;                        constexpr Int2 int2;
using Int3 = aliases::Into<aliases::Into<Sequence<ABC, SpaceDot>, Class4>, Class2>; constexpr Int3 int3;

using Api1 = ApplyInto<Sequence<ABC, SpaceDot>, Class2>; constexpr Api1 api1;
using Api2 = ApplyInto<Sequence<SpaceDot, ABC>, Class5>; constexpr Api2 api2;

using Con1 = Constant<_22, Const<1>>;       constexpr Con1 con1;
using Con2 = Constant<_23, Const<'t'>>;     constexpr Con2 con2;
using Con3 = Constant<_24, Const<true>>;    constexpr Con3 con3;
using Con4 = Constant<_25, Const<nullptr>>; constexpr Con4 con4;

using Def1 = aliases::Defaulted<_22, int>;    constexpr Def1 def1;
using Def2 = aliases::Defaulted<_23, Class3>; constexpr Def2 def2;

struct Cus1 : Custom<Cus1>
{
	using value_type = ::value_type;

	static consteval auto get_parser()
	{
		return _25{} % map<transform>;
	}

	static constexpr std::size_t transform_impl(const std::tuple<std::vector<Output<char>>, std::optional<Output<char>>>& tup)
	{
		const auto& [vec, opt] = tup;
		return 3 * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
	}

	static constexpr std::size_t transform_impl(const std::tuple<std::vector<Output<wchar_t>>, std::optional<Output<wchar_t>>>& tup)
	{
		const auto& [vec, opt] = tup;
		return 3 * vec.size() * (not opt ? 1 : *opt == L"abc" ? 2 : 3);
	}

	static constexpr std::size_t transform_impl(const std::tuple<std::vector<Output<int>>, std::optional<Output<int>>>& tup)
	{
		const auto& [vec, opt] = tup;
		return 3 * vec.size() * (not opt ? 1 : *opt == e<int>("abc") ? 2 : 3);
	}

	static constexpr auto transform = []<class T>(const std::tuple<std::vector<Output<T>>, std::optional<Output<T>>>&tup)
	{
		return transform_impl(tup);
	};
};
constexpr Cus1 cus1;

struct Cus2 : Custom<Cus2, ::value_type>
{
	using result_type = std::size_t;

	static consteval auto get_parser()
	{
		return _12{} % constant<(int)0>;
	}
};
constexpr Cus2 cus2;

#define DIVERGENT_SAMPLES              \
	(Joi1) (Joi2) (Joi3) (Joi4) (Joi5) \
	(Map1) (Map2) (Map3) (Map4)        \
	(Apt1) (Apt2)                      \
	(Int1) (Int2) (Int3)               \
	(Api1) (Api2)                      \
	(Con1) (Con2) (Con3) (Con4)        \
	(Def1) (Def2)                      \
	(Cus1) (Cus2)
