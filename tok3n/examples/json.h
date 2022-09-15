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
	constexpr auto to_integer = [](const std::tuple<std::string_view, std::vector<std::string_view>>& tuple) -> int64_t
	{
		int64_t ret = to_digit(std::get<0>(tuple));
		auto& vec = std::get<1>(tuple);
		if (not vec.empty())
			return vector_to_integer(vec, ret);
		else
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

	constexpr auto natural_number = (zero % fn<to_digit>) | ((nonzerodigit >> *digit) % fn<to_integer>);
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

	constexpr auto hex_to_sv = [](const std::tuple<std::string_view, std::string_view, std::string_view, std::string_view, std::string_view>& tuple) -> std::string_view
	{
		const char* begin = &std::get<0>(tuple).front();
		const char* last = &std::get<4>(tuple).back();
		return { begin, last + 1 };
	};

	constexpr auto hex = (u >> digit >> digit >> digit >> digit) % fn<hex_to_sv>;
	constexpr auto control = OneChar<"\"/\\bfnrt">{} | hex;

	constexpr auto flatten_2_tuple_sv = [](const std::tuple<std::string_view, std::string_view>& tuple) -> std::string_view
	{
		const char* begin = &std::get<0>(tuple).front();
		const char* last = &std::get<1>(tuple).back();
		return { begin, last + 1 };
	};

	constexpr auto valid_char = !(quote | backslash) | ((backslash >> control) % fn<flatten_2_tuple_sv>);

	constexpr auto to_string = [](const std::tuple<std::string_view, std::vector<std::string_view>, std::string_view>& tuple) -> std::string_view
	{
		auto& vec = std::get<1>(tuple);
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

constexpr auto string = (quote >> *valid_char >> quote) % fn<to_string>;
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
};
struct JsonArrayParser
{
	using result_type = array_t;

	static constexpr Result<result_type> parse(Input input);
};
struct JsonValueParser
{
	using result_type = value_t;

	static constexpr Result<result_type> parse(Input input);
};

constexpr Result<object_t> JsonObjectParser::parse(Input input)
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

	constexpr auto the_parser = left_brace >> (object | (whitespace % fn<get_whitespace>)) >> right_brace;

	constexpr auto get_parser = [](const std::tuple<std::string_view, object_t, std::string_view>& tuple) -> object_t
	{
		return std::get<1>(std::move(tuple));
	};

	return (the_parser % fn<get_parser>).parse(input);
}

constexpr Result<array_t> JsonArrayParser::parse(Input input)
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

	constexpr auto the_parser = left_bracket >> (values | (whitespace % fn<get_whitespace>)) >> right_bracket;
	
	constexpr auto get_parser = [](const std::tuple<std::string_view, array_t, std::string_view>& tuple) -> array_t
	{
		return std::get<1>(std::move(tuple));
	};

	return (the_parser % fn<get_parser>).parse(input);
}

constexpr Result<value_t> JsonValueParser::parse(Input input)
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
	
	constexpr auto get_parser = [](const std::tuple<std::string_view, value_t, std::string_view>& tuple) -> value_t
	{
		return std::get<1>(std::move(tuple));
	};

	constexpr auto the_parser = (whitespace >> value_parser >> whitespace) % fn<get_parser>;
	
	return the_parser.parse(input);
}

}
