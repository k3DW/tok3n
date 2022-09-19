#pragma once
#include "parsers/parsers.h"
#include "operators/operators.h"
#include <map>
#include <variant>

namespace k3::examples::json_parser
{

using namespace k3::parser;



inline namespace basic
{

	constexpr IsOneChar auto minus        = OneChar<'-'>{};
	constexpr IsOneChar auto signs        = OneChar<"+-">{};
	constexpr IsOneChar auto zero         = OneChar<'0'>{};
	constexpr IsOneChar auto point        = OneChar<'.'>{};
	constexpr IsOneChar auto digit        = OneChar<"0123456789">{};
	constexpr IsOneChar auto nonzerodigit = OneChar<"123456789">{};
	constexpr IsOneChar auto Ee           = OneChar<"Ee">{};

	constexpr IsOneChar auto quote          = OneChar<'"'>{};
	constexpr IsOneChar auto backslash      = OneChar<'\\'>{};
	constexpr IsOneChar auto u              = OneChar<"u">{};

	constexpr IsOneChar auto comma         = OneChar<','>{};
	constexpr IsOneChar auto colon         = OneChar<':'>{};
	constexpr IsOneChar auto left_brace    = OneChar<'{'>{};
	constexpr IsOneChar auto right_brace   = OneChar<'}'>{};
	constexpr IsOneChar auto left_bracket  = OneChar<'['>{};
	constexpr IsOneChar auto right_bracket = OneChar<']'>{};

}



struct number_t
{
	int64_t integer;
	std::optional<int64_t> fraction;
	std::optional<int64_t> exponent;
};

inline namespace number_impl
{

	constexpr auto get_zero = [](std::string_view) -> int64_t
	{
		return 0;
	};
	constexpr auto sv_to_int = [](std::string_view str) -> int64_t
	{
		int64_t ret = 0;
		for (char c : str)
			ret = (ret * 10) + (c - '0');
		return ret;
	};
	constexpr auto give_sign = [](const std::tuple<std::optional<std::string_view>, int64_t>& tuple) -> int64_t
	{
		auto& opt = std::get<0>(tuple);
		if (opt.has_value())
		{
			if (*opt == "+")
				return std::get<1>(tuple);
			else if (*opt == "-")
				return -std::get<1>(tuple);
			else throw;
		}
		else
			return std::get<1>(tuple);
	};

	constexpr auto any_digits = +digit % flatten % fn<sv_to_int>;
	static_assert(std::same_as<decltype(any_digits)::result_type, int64_t>);

	constexpr auto natural_number = (zero % fn<get_zero>) | ((nonzerodigit >> *digit) % flatten % fn<sv_to_int>);
	static_assert(std::same_as<decltype(natural_number)::result_type, int64_t>);

	constexpr auto integer = (~minus >> natural_number) % fn<give_sign>;
	static_assert(std::same_as<decltype(integer)::result_type, int64_t>);
		
	constexpr auto fraction = ignore(point) >> any_digits;
	static_assert(std::same_as<decltype(fraction)::result_type, int64_t>);

	constexpr auto exponent = (ignore(Ee) >> ~signs >> any_digits) % fn<give_sign>;
	static_assert(std::same_as<decltype(exponent)::result_type, int64_t>);

	constexpr auto to_number = [](const std::tuple<int64_t, std::optional<int64_t>, std::optional<int64_t>>& tuple) -> number_t
	{
		return { .integer = std::get<0>(tuple), .fraction = std::get<1>(tuple), .exponent = std::get<2>(tuple) };
	};

}

constexpr auto number = (integer >> ~fraction >> ~exponent) % fn<to_number>;
static_assert(std::same_as<decltype(number)::result_type, number_t>);



inline namespace string_impl
{

	constexpr auto hex = (u >> digit >> digit >> digit >> digit) % flatten;
	constexpr auto control = OneChar<"\"/\\bfnrt">{} | hex;

	constexpr auto valid_char = !(quote | backslash) | ((backslash >> control) % flatten);

}

constexpr auto string = ignore(quote) >> (*valid_char % flatten) >> ignore(quote);
static_assert(std::same_as<decltype(string)::result_type, std::string_view>);



inline namespace whitespace_impl
{

	template <class T>
	constexpr auto empty_value = [](auto&&) -> T { return {}; };

}

constexpr auto whitespace = *OneChar<"\t\n\r ">{} % flatten;
static_assert(std::same_as<decltype(whitespace)::result_type, std::string_view>);

template <class T>
constexpr auto whitespace_as = *OneChar<"\t\n\r ">{} % fn<empty_value<T>>;



struct JsonObjectParser;
struct JsonArrayParser;
struct JsonValueParser;

}



namespace k3::examples::json_parser
{

using namespace k3::parser;



struct object_t;
struct array_t;
struct value_t;

struct object_t
{
	std::map<std::string, value_t> data;
};
struct array_t
{
	std::vector<value_t> data;
};
struct value_t
{
	std::variant<std::string, number_t, object_t, array_t, bool, nullptr_t> data;
};



struct JsonObjectParser : CustomBase
{
	using result_type = object_t;

	static constexpr Result<result_type> parse(Input input);
	static constexpr Result<void> lookahead(Input input);

	static consteval auto get_parser();
};
struct JsonArrayParser : CustomBase
{
	using result_type = array_t;

	static constexpr Result<result_type> parse(Input input);
	static constexpr Result<void> lookahead(Input input);

	static consteval auto get_parser();
};
struct JsonValueParser : CustomBase
{
	using result_type = value_t;

	static constexpr Result<result_type> parse(Input input);
	static constexpr Result<void> lookahead(Input input);

	static consteval auto get_parser();
};

consteval auto JsonObjectParser::get_parser()
{
	using pair_t = std::pair<std::string_view, value_t>;

	constexpr auto get_pair = [](const std::tuple<std::string_view, value_t>& tuple) -> pair_t
	{
		return { std::get<0>(std::move(tuple)), std::get<1>(std::move(tuple)) };
	};

	constexpr auto pair = (ignore(whitespace) >> string >> ignore(whitespace) >> ignore(colon) >> JsonValueParser{}) % fn<get_pair>;

	constexpr auto get_object = [](const std::vector<pair_t>& vec) -> object_t
	{
		object_t object{};
	
		for (const pair_t& pair : vec)
			object.data.insert(pair);
	
		return object;
	};

	constexpr auto object = delimit(pair, comma) % fn<get_object>;

	constexpr auto the_parser = ignore(left_brace) >> (object | whitespace_as<object_t>) >> ignore(right_brace);

	return the_parser;
}

constexpr Result<object_t> JsonObjectParser::parse(Input input) { return decltype(get_parser())::parse(input); }
constexpr Result<void> JsonObjectParser::lookahead(Input input) { return decltype(get_parser())::lookahead(input); }

consteval auto JsonArrayParser::get_parser()
{
	constexpr auto get_array = [](const std::vector<value_t>& vec) -> array_t
	{
		array_t arr;

		for (const value_t& value : vec)
			arr.data.push_back(value);

		return arr;
	};

	constexpr auto values = delimit(JsonValueParser{}, comma) % fn<get_array>;

	constexpr auto the_parser = ignore(left_bracket) >> (values | whitespace_as<array_t>) >> ignore(right_bracket);

	return the_parser;
}

constexpr Result<array_t> JsonArrayParser::parse(Input input)  { return decltype(get_parser())::parse(input); }
constexpr Result<void> JsonArrayParser::lookahead(Input input) { return decltype(get_parser())::lookahead(input); }

consteval auto JsonValueParser::get_parser()
{
	constexpr auto get_value_string = [](std::string_view str) -> value_t
	{
		return { .data = std::string(str) };
	};
	constexpr auto get_value_number = [](number_t num) -> value_t
	{
		return { .data = num };
	};
	constexpr auto get_value_object = [](const object_t& object) -> value_t
	{
		return { .data = std::move(object) };
	};
	constexpr auto get_value_array = [](const array_t& array) -> value_t
	{
		return { .data = std::move(array) };
	};
	constexpr auto get_value_true = [](std::string_view) -> value_t
	{
		return { .data = true };
	};
	constexpr auto get_value_false = [](std::string_view) -> value_t
	{
		return { .data = false };
	};
	constexpr auto get_value_null = [](std::string_view) -> value_t
	{
		return { .data = nullptr };
	};


	constexpr auto value_parser =
		(string             % fn<get_value_string>) |
		(number             % fn<get_value_number>) |
		(JsonObjectParser{} % fn<get_value_object>) |
		(JsonArrayParser{}  % fn<get_value_array>)  |
		(Literal<"true">{}  % fn<get_value_true>)   |
		(Literal<"false">{} % fn<get_value_false>)  |
		(Literal<"null">{}  % fn<get_value_null>);

	constexpr auto the_parser = ignore(whitespace) >> value_parser >> ignore(whitespace);
	
	return the_parser;
}

constexpr Result<value_t> JsonValueParser::parse(Input input)  { return decltype(get_parser())::parse(input); }
constexpr Result<void> JsonValueParser::lookahead(Input input) { return decltype(get_parser())::lookahead(input); }

}
