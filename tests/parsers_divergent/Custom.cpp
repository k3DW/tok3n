#include "pch.h"

TOK3N_BEGIN_NAMESPACE(tests)

using namespace samples::all;

struct Cus : Custom<Cus>
{
	using result_type = std::size_t;

	static consteval auto get_parser()
	{
		return Sub2::_5{} % fn<transform>;
	}

	static constexpr std::size_t transform(const std::tuple<std::vector<std::string_view>, std::optional<std::string_view>>& tup)
	{
		const auto& [vec, opt] = tup;
		return 3 * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
	}
};

inline void requirements()
{
	assert
		, IsParser<Cus, CustomType, std::size_t>
		;
}

inline void parse_Transform()
{
	assert
		, parse<Cus>("abcabcabcabc??").success(36, "")
		, parse<Cus>("abcabcabcabc").success(12, "")
		, parse<Cus>("abcabcabcabc ??").success(12, " ??")
		, parse<Cus>("abc").success(3, "")
		, parse<Cus>(" abc").failure()
		, parse<Cus>("").failure()
		;
}

TOK3N_END_NAMESPACE(tests)
