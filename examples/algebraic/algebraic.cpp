#pragma once
#include <k3/tok3n.h>
#include <format>
#include <variant>
#include <iostream>

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

constexpr auto ws  = *"\t\n\r "_one % ignore;
constexpr auto dgt = "0123456789"_one;

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
        constexpr auto exponent = join(ignore("Ee"_one) >> ~"-"_lit >> +dgt);

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
	using result_type = std::vector<factor::result_type>;
	static consteval auto get_parser();
};

struct expr : Custom<expr>
{
	using result_type = std::vector<term::result_type>;
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
	return (ws >> powterm{}) % delimit(ws >> "^"_one);
}

consteval auto term::get_parser()
{
	return (ws >> factor{}) % delimit(ws >> "*/"_one);
}

consteval auto expr::get_parser()
{
	return (ws >> term{}) % delimit(ws >> "+-"_one);
}

consteval auto powterm::get_parser()
{
	constexpr auto bracketed = "("_ign >> ws >> expr{} >> ws >> ")"_ign;
	constexpr auto negated = "-"_ign >> ws >> expr{};
	return into_choice<result_type>
		(
			bracketed % into<result_type::bracketed_expr>,
			negated % into<result_type::negated_expr>,
			number{}
	);
}



struct input : Custom<input>
{
	static constexpr auto parser = complete(ws >> expr{} >> ws);
	static consteval auto get_parser() { return parser; }

	using result_type = decltype(parser)::result_type;
};



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

	void print(const powterm::result_type& val, std::size_t tabs);
	void print(const powterm::result_type::bracketed_expr& val, std::size_t tabs);
	void print(const powterm::result_type::negated_expr& val, std::size_t tabs);
	void print(const number::result_type& val, std::size_t tabs);
	void print(const expr::result_type& val, std::size_t tabs);
	void print(const term::result_type& val, std::size_t tabs);
	void print(const factor::result_type& val, std::size_t tabs);

	void print(const powterm::result_type& val, std::size_t tabs)
	{
		autoprint a("Powterm", tabs);
		if (std::holds_alternative<powterm::result_type::bracketed_expr>(val.data))
			print(std::get<powterm::result_type::bracketed_expr>(val.data), tabs + 1);
		else if (std::holds_alternative<powterm::result_type::negated_expr>(val.data))
			print(std::get<powterm::result_type::negated_expr>(val.data), tabs + 1);
		else
			print(std::get<number::result_type>(val.data), tabs + 1);
	}
	void print(const powterm::result_type::bracketed_expr& val, std::size_t tabs)
	{
		autoprint a("Bracketed Expr", tabs);
		print(val.data, tabs + 1);
	}
	void print(const powterm::result_type::negated_expr& val, std::size_t tabs)
	{
		autoprint a("Negated Expr", tabs);
		print(val.data, tabs + 1);
	}
	void print(const number::result_type& val, std::size_t tabs)
	{
		print("Number : ", tabs);

		std::cout << val.integer;
		if (val.decimal)
			std::cout << "." << *val.decimal;
		if (val.exponent)
			std::cout << "e" << *val.exponent;
	}
	void print(const expr::result_type& val, std::size_t tabs)
	{
		autoprint a("Expr", tabs);

		for (std::size_t i = 0; i != val.size(); ++i)
		{
			print(val[i], tabs + 1);
			if (i != val.size() - 1)
				std::cout << ",\n";
		}
	}
	void print(const term::result_type& val, std::size_t tabs)
	{
		autoprint a("Term", tabs);

		for (std::size_t i = 0; i != val.size(); ++i)
		{
			print(val[i], tabs + 1);
			if (i != val.size() - 1)
				std::cout << ",\n";
		}
	}
	void print(const factor::result_type& val, std::size_t tabs)
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



int main()
{
	auto result = input::parse("4 ^ (2 + 4 * 6) + 1 * 3");
	if (result)
		print::print(*result, 0);
	else
		std::cout << "Parse failure.\n";
}
