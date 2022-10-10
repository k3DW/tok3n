#include "tests/utility.h"

TOK3N_BEGIN_NAMESPACE_TESTS(adaptor::Transform)

using L1 = Literal<"abc">;
using L2 = Literal<"??">;

constexpr std::size_t func1(std::vector<std::string_view>&& vec)
{
	return vec.size();
}

constexpr auto func2 = [](const std::optional<std::string_view>& opt) -> std::vector<char>
{
	if (not opt.has_value())
		return {};
	else
	{
		auto& sv = *opt;
		return { sv.begin(), sv.end() };
	}
};

constexpr struct func3_t
{
	constexpr bool operator()(std::tuple<std::string_view, std::vector<std::string_view>>&& tup) const
	{
		auto&& [sv, vec] = std::move(tup);
		return vec.size() % 2 == 0;
	}
} func3;

struct func4
{
	constexpr func4(int multiply_by)
		: multiply_by(multiply_by) {}

	int multiply_by;

	constexpr std::size_t operator()(const std::tuple<std::vector<std::string_view>, std::optional<std::string_view>>& tup) const
	{
		const auto& [vec, opt] = tup;
		return multiply_by * vec.size() * (not opt ? 1 : *opt == "abc" ? 2 : 3);
	}
};

using T1 = Transform<OneOrMore<L1>, func1>;
constexpr T1 t1;
using T2 = Transform<Maybe<Choice<L1, L2>>, func2>;
constexpr T2 t2;
using T3 = Transform<Sequence<L1, ZeroOrMore<L2>>, func3>;
constexpr T3 t3;
using T4 = Transform<Sequence<OneOrMore<L1>, Maybe<Choice<L1, L2>>>, func4(3)>;
constexpr T4 t4;

void requirements()
{
	assert
		, is_parser<T1>
		, parser_type_of<T1>.is_Transform
		, result_of<T1>.is<std::size_t>
		, T1::parse == t1.parse
		, T1::lookahead == t1.lookahead
		
		, is_parser<T2>
		, parser_type_of<T2>.is_Transform
		, result_of<T2>.is<std::vector<char>>
		, T2::parse == t2.parse
		, T2::lookahead == t2.lookahead
		
		, is_parser<T3>
		, parser_type_of<T3>.is_Transform
		, result_of<T3>.is<bool>
		, T3::parse == t3.parse
		, T3::lookahead == t3.lookahead
		
		, is_parser<T4>
		, parser_type_of<T4>.is_Transform
		, result_of<T4>.is<std::size_t>
		, T4::parse == t4.parse
		, T4::lookahead == t4.lookahead
		;
}

void parse_Transform()
{
	assert
		, parse<T1>("abcabcabcab").success(3, "ab")
		, parse<T1>("").failure("")
		, parse<T1>("ab").failure("ab")
		, parse<T1>("abc").success(1, "")
		
		, parse<T2>("abcabc").success({ 'a', 'b', 'c' }, "abc")
		, parse<T2>("a??bcabc").success({}, "a??bcabc")
		, parse<T2>("").success({}, "")
		, parse<T2>("??abcabc").success({ '?', '?' }, "abcabc")
		, parse<T2>(" ??abcabc").success({}, " ??abcabc")
		
		, parse<T3>("abc???????").success(false, "?")
		, parse<T3>("??abc???????").failure("??abc???????")
		, parse<T3>("abc??abc???????").success(false, "abc???????")
		, parse<T3>("abc ??abc???????").success(true, " ??abc???????")
		, parse<T3>("").failure("")
		
		, parse<T4>("abcabcabcabc??").success(36, "")
		, parse<T4>("abcabcabcabc").success(12, "")
		, parse<T4>("abcabcabcabc ??").success(12, " ??")
		, parse<T4>("abc").success(3, "")
		, parse<T4>(" abc").failure(" abc")
		, parse<T4>("").failure("")
		;
}

void transform_operator()
{
	constexpr L1 l1;
	constexpr L2 l2;

	assert
		, t1 == +l1 % fn<func1>
		, t2 == ~(l1 | l2) % fn<func2>
		, t3 == (l1 >> *l2) % fn<func3>
		, t4 == (+l1 >> ~(l1 | l2)) % fn<func4(3)>
		, t4 != (+l1 >> ~(l1 | l2)) % fn<func4(2)>
		;
}

TOK3N_END_NAMESPACE_TESTS(adaptor::Transform)
