#pragma once
#include "parser.h"
#include <cmath>
#include <charconv>

double evaluate(const expr::result_type& val);
double evaluate(const term::result_type& val);
double evaluate(const factor::result_type& val);
double evaluate(const powterm::result_type& val);
double evaluate(const powterm::result_type::bracketed_expr& val);
double evaluate(const powterm::result_type::negated_expr& val);
double evaluate(const number::result_type& val);

double evaluate(const expr::result_type& val)
{
	using Type = double(*)(const term::result_type&);
	auto out = std::ranges::fold_left_first(val | std::views::transform((Type)evaluate), std::plus{});
	return out.value_or(0);
}

double evaluate(const term::result_type& val)
{
	using Type = double(*)(const factor::result_type&);
	auto out = std::ranges::fold_left_first(val | std::views::transform((Type)evaluate), std::multiplies{});
	return out.value_or(0);
}

double evaluate(const factor::result_type& val)
{
	using Type = double(*)(const powterm::result_type&);
	using OpType = double(*)(double, double);
	auto out = std::ranges::fold_right_last(val | std::views::transform((Type)evaluate), (OpType)std::pow);
	return out.value_or(0);
}

double evaluate(const powterm::result_type& val)
{
	return std::visit([](const auto& v) -> double { return evaluate(v); }, val.data);
}

double evaluate(const powterm::result_type::bracketed_expr& val)
{
	return evaluate(val.data);
}

double evaluate(const powterm::result_type::negated_expr& val)
{
	return -evaluate(val.data);
}

double evaluate(const number::result_type& val)
{
	auto real = std::string(val.integer);
	if (val.decimal)
	{
		real += ".";
		real += *val.decimal;
	}

	double value;
	if (std::from_chars(real.data(), real.data() + real.size(), value).ec != std::errc{})
		throw;

	if (not val.exponent)
		return value;

	int exp;
	if (std::from_chars(val.exponent->data(), val.exponent->data() + val.exponent->size(), exp).ec != std::errc{})
		throw;

	return std::pow(value, exp);
}
