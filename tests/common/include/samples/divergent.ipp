using Joi1 = k3::tok3n::Join<_21>; constexpr Joi1 joi1;
using Joi2 = k3::tok3n::Join<_22>; constexpr Joi2 joi2;
using Joi3 = k3::tok3n::Join<_23>; constexpr Joi3 joi3;
using Joi4 = k3::tok3n::Join<_24>; constexpr Joi4 joi4;
using Joi5 = k3::tok3n::Join<_25>; constexpr Joi5 joi5;

using Map1 = k3::tok3n::Map<_22, k3::tok3n::detail::integral_constant<func1>>;    constexpr Map1 tra1;
using Map2 = k3::tok3n::Map<_23, k3::tok3n::detail::integral_constant<func2>>;    constexpr Map2 tra2;
using Map3 = k3::tok3n::Map<_24, k3::tok3n::detail::integral_constant<func3>>;    constexpr Map3 tra3;
using Map4 = k3::tok3n::Map<_25, k3::tok3n::detail::integral_constant<func4(3)>>; constexpr Map4 tra4;

using Apm1 = k3::tok3n::aliases::ApplyMap<_24, k3::tok3n::detail::integral_constant<func3_apply>>;    constexpr Apm1 apm1;
using Apm2 = k3::tok3n::aliases::ApplyMap<_25, k3::tok3n::detail::integral_constant<func4_apply(3)>>; constexpr Apm2 apm2;

using Int1 = k3::tok3n::aliases::Into<SpaceDot, Class1>;                                                             constexpr Int1 int1;
using Int2 = k3::tok3n::aliases::Into<k3::tok3n::Sequence<ABC, SpaceDot>, Class2>;                                   constexpr Int2 int2;
using Int3 = k3::tok3n::aliases::Into<k3::tok3n::aliases::Into<k3::tok3n::Sequence<ABC, SpaceDot>, Class4>, Class2>; constexpr Int3 int3;

using Api1 = k3::tok3n::aliases::ApplyInto<k3::tok3n::Sequence<ABC, SpaceDot>, Class2>; constexpr Api1 api1;
using Api2 = k3::tok3n::aliases::ApplyInto<k3::tok3n::Sequence<SpaceDot, ABC>, Class5>; constexpr Api2 api2;

using Con1 = k3::tok3n::aliases::Constant<_22, k3::tok3n::detail::integral_constant<1>>;       constexpr Con1 con1;
using Con2 = k3::tok3n::aliases::Constant<_23, k3::tok3n::detail::integral_constant<'t'>>;     constexpr Con2 con2;
using Con3 = k3::tok3n::aliases::Constant<_24, k3::tok3n::detail::integral_constant<true>>;    constexpr Con3 con3;
using Con4 = k3::tok3n::aliases::Constant<_25, k3::tok3n::detail::integral_constant<nullptr>>; constexpr Con4 con4;

using Def1 = k3::tok3n::aliases::Defaulted<_22, int>;    constexpr Def1 def1;
using Def2 = k3::tok3n::aliases::Defaulted<_23, Class3>; constexpr Def2 def2;

struct Cus1 : k3::tok3n::Custom<Cus1>
{
	using value_type = ::value_type;

	static consteval auto get_parser()
	{
		return _25{} % k3::tok3n::map<transform>;
	}

	static constexpr std::size_t transform_impl(const std::tuple<std::vector<k3::tok3n::detail::output_span<char>>, std::optional<k3::tok3n::detail::output_span<char>>>& tup)
	{
		const auto& [vec, opt] = tup;
		return 3 * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
	}

	static constexpr std::size_t transform_impl(const std::tuple<std::vector<k3::tok3n::detail::output_span<wchar_t>>, std::optional<k3::tok3n::detail::output_span<wchar_t>>>& tup)
	{
		const auto& [vec, opt] = tup;
		return 3 * vec.size() * (not opt ? 1 : *opt == L"abc" ? 2 : 3);
	}

	static constexpr std::size_t transform_impl(const std::tuple<std::vector<k3::tok3n::detail::output_span<int>>, std::optional<k3::tok3n::detail::output_span<int>>>& tup)
	{
		const auto& [vec, opt] = tup;
		return 3 * vec.size() * (not opt ? 1 : *opt == e<int>("abc") ? 2 : 3);
	}

	static constexpr auto transform = []<class T>(const std::tuple<std::vector<k3::tok3n::detail::output_span<T>>, std::optional<k3::tok3n::detail::output_span<T>>>&tup)
	{
		return transform_impl(tup);
	};
};
constexpr Cus1 cus1;

struct Cus2 : k3::tok3n::Custom<Cus2, ::value_type>
{
	using result_type = std::size_t;

	static consteval auto get_parser()
	{
		return _12{} % k3::tok3n::constant<(int)0>;
	}
};
constexpr Cus2 cus2;

#define DIVERGENT_SAMPLES              \
	(Joi1) (Joi2) (Joi3) (Joi4) (Joi5) \
	(Map1) (Map2) (Map3) (Map4)        \
	(Apm1) (Apm2)                      \
	(Int1) (Int2) (Int3)               \
	(Api1) (Api2)                      \
	(Con1) (Con2) (Con3) (Con4)        \
	(Def1) (Def2)                      \
	(Cus1) (Cus2)
