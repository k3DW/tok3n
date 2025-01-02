// Copyright 2023-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#pragma once
#include "parser.hpp"
#include <cmath>
#include <charconv>
#include <string>

double evaluate(const expr::result_type& val);
double evaluate(const term::result_type& val);
double evaluate(const factor::result_type& val);
double evaluate(const powterm::result_type& val);
double evaluate(const powterm::result_type::bracketed_expr& val);
double evaluate(const powterm::result_type::negated_expr& val);
double evaluate(const number::result_type& val);

double evaluate(const expr::result_type& val)
{
	auto& [values, delimiters] = val;

	auto it_val = values.begin();
	auto it_delim = delimiters.begin();

	const auto end_val = values.end();
	const auto end_delim = delimiters.end();

	double output = evaluate(*it_val);
	++it_val;

	// This would be much better with zip_transform
	for (; it_val != end_val && it_delim != end_delim; ++it_val, ++it_delim)
	{
		switch (it_delim->front())
		{
		break; case '+': output += evaluate(*it_val);
		break; case '-': output -= evaluate(*it_val);
		break; default: throw;
		}
	}

	return output;
}

double evaluate(const term::result_type& val)
{
	auto& [values, delimiters] = val;

	auto it_val = values.begin();
	auto it_delim = delimiters.begin();

	const auto end_val = values.end();
	const auto end_delim = delimiters.end();

	double output = evaluate(*it_val);
	++it_val;

	// This would be much better with zip_transform
	for (; it_val != end_val && it_delim != end_delim; ++it_val, ++it_delim)
	{
		switch (it_delim->front())
		{
		break; case '*': output *= evaluate(*it_val);
		break; case '/': output /= evaluate(*it_val);
		break; default: throw;
		}
	}

	return output;
}

double evaluate(const factor::result_type& val)
{
	auto it = val.rbegin();
	const auto end = val.rend();

	double output = evaluate(*it);
	++it;

	// This would be much better with fold_right_last
	for (; it != end; ++it)
	{
		output = std::pow(evaluate(*it), output);
	}

	return output;
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

template <std::same_as<double> T>
void from_chars(const std::string& str, T& value)
{
	if constexpr (requires { std::from_chars(str.data(), str.data() + str.size(), value); })
	{
		if (std::from_chars(str.data(), str.data() + str.size(), value).ec != std::errc{})
			throw std::invalid_argument("Invalid argument");
	}
	else
	{
		value = std::stod(str);
	}
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
	from_chars(real, value);

	if (not val.exponent)
		return value;

	int exp;
	if (std::from_chars(val.exponent->data(), val.exponent->data() + val.exponent->size(), exp).ec != std::errc{})
		throw;

	return std::pow(value, exp);
}
