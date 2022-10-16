#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::Custom)

struct CC : Custom<CC>
{
	using result_type = std::size_t;

	static consteval auto get_parser()
	{
		constexpr auto l1 = Literal<"abc">{};
		constexpr auto l2 = Literal<"??">{};
		return (+l1 >> ~(l1 | l2)) % fn<transform>;
	}

	static constexpr std::size_t transform(const std::tuple<std::vector<std::string_view>, std::optional<std::string_view>>& tup)
	{
		const auto& [vec, opt] = tup;
		return 3 * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
	}
};

constexpr CC cc;

void requirements()
{
	assert
		, is_parser<CC>
		, parser_type_of<CC>.is_Custom
		, result_of<CC>.is<std::size_t>
		;
}

void parse_Transform()
{
	assert
		, parse<CC>("abcabcabcabc??").success(36, "")
		, parse<CC>("abcabcabcabc").success(12, "")
		, parse<CC>("abcabcabcabc ??").success(12, " ??")
		, parse<CC>("abc").success(3, "")
		, parse<CC>(" abc").failure()
		, parse<CC>("").failure()
		;
}

TOK3N_END_NAMESPACE_TESTS(adaptor::Custom)
