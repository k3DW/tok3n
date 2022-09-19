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

	constexpr auto to_digit = [](std::string_view sv) -> int64_t
	{
		return sv.front() - '0';
	};
	constexpr auto vector_to_integer = [](const std::vector<std::string_view>& vec, int64_t start = 0) -> int64_t
	{
		int64_t ret = start;
		for (auto& sv : vec)
			ret = (ret * 10) + to_digit(sv);
		return ret;
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
		if (opt.has_value() && *opt == "-")
			return -std::get<1>(tuple);
		else
			return std::get<1>(tuple);
	};

	constexpr auto natural_number = (zero % fn<to_digit>) | ((nonzerodigit >> *digit) % flatten % fn<sv_to_int>);
	static_assert(std::same_as<decltype(natural_number)::result_type, int64_t>);

	constexpr auto integer = (~minus >> natural_number) % fn<give_sign>;
	static_assert(std::same_as<decltype(integer)::result_type, int64_t>);

	constexpr auto to_fraction = [](const std::tuple<std::string_view, std::vector<std::string_view>>& tuple) -> int64_t
	{
		return vector_to_integer(std::get<1>(tuple));
	};
	
	constexpr auto fraction = (point >> +digit) % fn<to_fraction>;

	constexpr auto to_exponent = [](const std::tuple<std::string_view, std::optional<std::string_view>, std::vector<std::string_view>>& tuple) -> int64_t
	{
		int64_t value = vector_to_integer(std::get<2>(tuple));

		auto& opt = std::get<1>(tuple);
		if (opt.has_value())
		{
			if (*opt == "+")
				return value;
			else // *opt == "-"
				return -value;
		}
		else
			return value;
	};

	constexpr auto exponent = (Ee >> ~signs >> +digit) % fn<to_exponent>;

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

	constexpr IsOneChar auto whitespacechar = OneChar<"\t\n\r ">{};

	constexpr auto flatten_whitespace = [](const std::vector<std::string_view>& vec) -> std::string_view
	{
		if (vec.empty())
			return "";
		else
		{
			const char* begin = &vec.front().front();
			const char* last = &vec.back().back();
			return { begin, last + 1 };
		}
	};

}

constexpr auto whitespace = *whitespacechar % fn<flatten_whitespace>;
static_assert(std::same_as<decltype(whitespace)::result_type, std::string_view>);



struct JsonObjectParser;
struct JsonArrayParser;
struct JsonValueParser;

}



namespace k3::parser
{

	template <>
	constexpr ParserType parser_type_v<k3::examples::json_parser::JsonObjectParser> = ParserType{ 100 };
	template <>
	constexpr ParserType parser_type_v<k3::examples::json_parser::JsonArrayParser> = ParserType{ 100 };
	template <>
	constexpr ParserType parser_type_v<k3::examples::json_parser::JsonValueParser> = ParserType{ 100 };

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



struct JsonObjectParser
{
	using result_type = object_t;

	static constexpr Result<result_type> parse(Input input);
	static constexpr Result<void> lookahead(Input input);

	static consteval auto get_parser();
};
struct JsonArrayParser
{
	using result_type = array_t;

	static constexpr Result<result_type> parse(Input input);
	static constexpr Result<void> lookahead(Input input);

	static consteval auto get_parser();
};
struct JsonValueParser
{
	using result_type = value_t;

	static constexpr Result<result_type> parse(Input input);
	static constexpr Result<void> lookahead(Input input);

	static consteval auto get_parser();
};

consteval auto JsonObjectParser::get_parser()
{
	using pair_t = std::pair<std::string_view, value_t>;

	constexpr auto get_pair = [](const std::tuple<std::string_view, std::string_view, std::string_view, std::string_view, value_t>& tuple) -> pair_t
	{
		return { std::get<1>(std::move(tuple)), std::get<4>(std::move(tuple)) };
	};

	constexpr auto pair = (whitespace >> string >> whitespace >> colon >> JsonValueParser{}) % fn<get_pair>;

	constexpr auto get_object = [](const std::tuple<pair_t, std::vector<std::tuple<std::string_view, pair_t>>>& tuple) -> object_t
	{
		object_t object{};
		auto& map = object.data;

		map.insert(std::get<0>(std::move(tuple)));
		auto&& vec = std::get<1>(std::move(tuple));

		if (not vec.empty())
		{
			for (auto&& inner_tuple : std::move(vec))
				map.insert(std::get<1>(std::move(inner_tuple)));
		}

		return object;
	};

	constexpr auto get_whitespace = [](std::string_view str) -> object_t
	{
		return {};
	};

	constexpr auto object = (pair >> *(comma >> pair)) % fn<get_object>;

	constexpr auto the_parser = ignore(left_brace) >> (object | (whitespace % fn<get_whitespace>)) >> ignore(right_brace);

	return the_parser;
}

constexpr Result<object_t> JsonObjectParser::parse(Input input) { return decltype(get_parser())::parse(input); }
constexpr Result<void> JsonObjectParser::lookahead(Input input) { return decltype(get_parser())::lookahead(input); }

consteval auto JsonArrayParser::get_parser()
{
	constexpr auto get_array = [](const std::tuple<value_t, std::vector<std::tuple<std::string_view, value_t>>>& tuple) -> array_t
	{
		array_t arr;
		auto& data = arr.data;

		data.push_back(std::get<0>(std::move(tuple)));
		auto&& vec = std::get<1>(std::move(tuple));

		if (not vec.empty())
		{
			for (auto&& inner_tuple : std::move(vec))
				data.push_back(std::get<1>(std::move(inner_tuple)));
		}

		return arr;
	};

	constexpr auto get_whitespace = [](std::string_view str) -> array_t
	{
		return {};
	};

	constexpr auto values = (JsonValueParser{} >> *(comma >> JsonValueParser{})) % fn<get_array>;

	constexpr auto the_parser = ignore(left_bracket) >> (values | (whitespace % fn<get_whitespace>)) >> ignore(right_bracket);

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
