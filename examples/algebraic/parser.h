#pragma once
#include <k3/tok3n.h>
#include <variant>

using namespace k3::tok3n::operators;

/*

Example from https://www.nongnu.org/bnf/
(modified slightly because it has operator precedence in the wrong order)

input	::= ws expr ws eoi;

expr	::= ws term [{ws ('+'|'-') ws term}];
term	::= ws factor [{ws ('*'|'/') ws factor}];
factor	::= ws powterm [{ws '^' ws powterm}];
powterm	::= '(' ws expr ws ')' | '-' ws expr | number;

number	::= {dgt} ['.' {dgt}] [('e'|'E') ['-'] {dgt}];
dgt	::= '0'|'1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9';
ws	::= [{' '|'\t'|'\n'|'\r'}];

*/

constexpr auto ws = *"\t\n\r "_any % ignore;
constexpr auto dgt = "0123456789"_any;

struct number : Custom<number>
{
	struct result_type
	{
		std::string_view                integer;
		std::optional<std::string_view> decimal;
		std::optional<std::string_view> exponent;
	};

	static consteval auto get_parser()
	{
		constexpr auto integer = +dgt % join;
		constexpr auto fraction = join("."_ign >> +dgt);
		constexpr auto exponent = join(ignore("Ee"_any) >> ~"-"_all >> +dgt);

		return apply_into<result_type>(integer >> ~fraction >> ~exponent);
	}
};



struct powterm : Custom<powterm>
{
	struct result_type;
	static consteval auto get_parser();
};

struct factor : Custom<factor>
{
	using result_type = std::vector<powterm::result_type>;
	static consteval auto get_parser();
};

struct term : Custom<term>
{
	using result_type = std::pair<std::vector<factor::result_type>, std::vector<std::string_view>>;
	static consteval auto get_parser();
};

struct expr : Custom<expr>
{
	using result_type = std::pair<std::vector<term::result_type>, std::vector<std::string_view>>;
	static consteval auto get_parser();
};

struct powterm::result_type
{
	struct bracketed_expr { expr::result_type data; };
	struct negated_expr { expr::result_type data; };

	std::variant<bracketed_expr, negated_expr, number::result_type> data;
};



consteval auto factor::get_parser()
{
	return (ws >> powterm{}) % delimit(ws >> "^"_any % into<std::string_view>);
}

consteval auto term::get_parser()
{
	return (ws >> factor{}) % delimit_keep(ws >> "*/"_any % into<std::string_view>);
}

consteval auto expr::get_parser()
{
	return (ws >> term{}) % delimit_keep(ws >> "+-"_any % into<std::string_view>);
}

consteval auto powterm::get_parser()
{
	constexpr auto bracketed = "("_ign >> ws >> expr{} >> ws >> ")"_ign;
	constexpr auto negated = "-"_ign >> ws >> expr{};
	return into<result_type>
	(
		bracketed % into<result_type::bracketed_expr> |
		negated % into<result_type::negated_expr> |
		number{}
	);
}



struct input : Custom<input>
{
	static constexpr auto parser = complete(ws >> expr{} >> ws);
	static consteval auto get_parser() { return parser; }
};
