#pragma once
#include "parser.h"
#include <iostream>

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
