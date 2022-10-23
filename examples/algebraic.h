#pragma once
#include "tok3n/tok3n.h"
#include <format>

TOK3N_BEGIN_NAMESPACE(examples::algebraic)

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

constexpr auto ws  = ignore(*OneChar<"\t\n\r ">{});
constexpr auto dgt = OneChar<"0123456789">{};

struct number_t
{
	std::string_view                integer;
	std::optional<std::string_view> decimal;
	std::optional<std::string_view> exponent;
};
namespace number_impl
{
	constexpr auto integer  = +dgt % join;
	constexpr auto decimal  = ~(ignore(OneChar<".">{}) >> +dgt % join);
	constexpr auto exponent = ~(ignore(OneChar<"Ee">{}) >> (~OneChar<"-">{} >> +dgt) % join);
}
constexpr auto number = (number_impl::integer >> number_impl::decimal >> number_impl::exponent) % into<number_t>;

struct powterm_t
{
	using factor_t  = std::vector<powterm_t>;
	using term_t    = std::vector<factor_t>;
	using expr_t    = std::vector<term_t>;

	struct bracketed_expr { expr_t data; };
	struct negated_expr   { expr_t data; };

	std::variant<bracketed_expr, negated_expr, number_t> data;
};
struct powterm : Custom<powterm>
{
	using result_type = powterm_t;
	static consteval auto get_parser();
};

constexpr auto factor = delimit(ws >> powterm{}, ws >> OneChar<"^">{});
constexpr auto term   = delimit(ws >> factor,    ws >> OneChar<"*/">{});
constexpr auto expr   = delimit(ws >> term,      ws >> OneChar<"+-">{});

consteval auto powterm::get_parser()
{
	constexpr auto bracketed = (ignore(OneChar<"(">{}) >> ws >> expr >> ws >> ignore(OneChar<")">{})) % into<powterm_t::bracketed_expr>;
	constexpr auto negated   = (ignore(OneChar<"-">{}) >> ws >> expr)                                 % into<powterm_t::negated_expr>;
	return
		bracketed % into<powterm_t> |
		negated   % into<powterm_t> |
		number    % into<powterm_t>;
}

constexpr auto input = ws >> expr >> ws;



namespace print
{

	std::string_view get_tabs(std::size_t tabs)
	{
		static const std::string all_tabs(1024, '\t');
		return { all_tabs.data(), tabs };
	}

	void print(std::string_view val, std::size_t tabs)
	{
		std::cout << get_tabs(tabs) << val;
	}

	struct autoprint
	{
		autoprint(std::string_view val, std::size_t tabs) : tabs(tabs)
		{
			print(val, tabs);
			std::cout << " :\n";
			print("{\n", tabs);
		}

		~autoprint()
		{
			std::cout << "\n";
			print("}", tabs);
		}

		autoprint(const autoprint&) = delete;
		autoprint(autoprint&&) = delete;
		autoprint& operator=(const autoprint&) = delete;
		autoprint& operator=(autoprint&&) = delete;

	private:
		std::size_t tabs;
	};

	void print(const powterm_t& val, std::size_t tabs);
	void print(const powterm_t::bracketed_expr& val, std::size_t tabs);
	void print(const powterm_t::negated_expr& val, std::size_t tabs);
	void print(const number_t& val, std::size_t tabs);
	void print(const powterm_t::expr_t& val, std::size_t tabs);
	void print(const powterm_t::term_t& val, std::size_t tabs);
	void print(const powterm_t::factor_t& val, std::size_t tabs);

	void print(const powterm_t& val, std::size_t tabs)
	{
		autoprint a("Powterm", tabs);
		if (std::holds_alternative<powterm_t::bracketed_expr>(val.data))
			print(std::get<powterm_t::bracketed_expr>(val.data), tabs + 1);
		else if (std::holds_alternative<powterm_t::negated_expr>(val.data))
			print(std::get<powterm_t::negated_expr>(val.data), tabs + 1);
		else
			print(std::get<number_t>(val.data), tabs + 1);
	}
	void print(const powterm_t::bracketed_expr& val, std::size_t tabs)
	{
		autoprint a("Bracketed Expr", tabs);
		print(val.data, tabs + 1);
	}
	void print(const powterm_t::negated_expr& val, std::size_t tabs)
	{
		autoprint a("Negated Expr", tabs);
		print(val.data, tabs + 1);
	}
	void print(const number_t& val, std::size_t tabs)
	{
		print("Number : ", tabs);

		std::cout << val.integer;
		if (val.decimal)
			std::cout << "." << *val.decimal;
		if (val.exponent)
			std::cout << "e" << *val.exponent;
	}
	void print(const powterm_t::expr_t& val, std::size_t tabs)
	{
		autoprint a("Expr", tabs);

		for (std::size_t i = 0; i != val.size(); ++i)
		{
			print(val[i], tabs + 1);
			if (i != val.size() - 1)
				std::cout << ",\n";
		}
	}
	void print(const powterm_t::term_t& val, std::size_t tabs)
	{
		autoprint a("Term", tabs);

		for (std::size_t i = 0; i != val.size(); ++i)
		{
			print(val[i], tabs + 1);
			if (i != val.size() - 1)
				std::cout << ",\n";
		}
	}
	void print(const powterm_t::factor_t& val, std::size_t tabs)
	{
		autoprint a("Factor", tabs);

		for (std::size_t i = 0; i != val.size(); ++i)
		{
			print(val[i], tabs + 1);
			if (i != val.size() - 1)
				std::cout << ",\n";
		}
	}

}



auto test()
{
	auto result = input.parse("1 + 2 * 3");
	if (result)
		print::print(*result, 0);
	else
		std::cout << "Parse failure.\n";
	return true;
}

TOK3N_END_NAMESPACE(examples::algebraic)
