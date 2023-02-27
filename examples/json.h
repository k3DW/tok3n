#pragma once
#include "tok3n/tok3n.h"
#include <map>
#include <variant>

TOK3N_BEGIN_NAMESPACE(examples::json_parser)



constexpr IsOneChar auto digit = "0123456789"_one;



inline namespace number_impl
{

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

	constexpr auto any_digits = +digit % join % fn<sv_to_int>;
	static_assert(std::same_as<decltype(any_digits)::result_type, int64_t>);

	constexpr auto natural_number = ("0"_lit | join("123456789"_one >> *digit)) % fn<sv_to_int>;
	static_assert(std::same_as<decltype(natural_number)::result_type, int64_t>);

	constexpr auto integer = (~"-"_lit >> natural_number) % fn<give_sign>;
	static_assert(std::same_as<decltype(integer)::result_type, int64_t>);
		
	constexpr auto fraction = "."_ign >> any_digits;
	static_assert(std::same_as<decltype(fraction)::result_type, int64_t>);

	constexpr auto exponent = (ignore("Ee"_one) >> ~"+-"_one >> any_digits) % fn<give_sign>;
	static_assert(std::same_as<decltype(exponent)::result_type, int64_t>);

}

struct number_t
{
	int64_t integer;
	std::optional<int64_t> fraction;
	std::optional<int64_t> exponent;
};

constexpr auto number = (integer >> ~fraction >> ~exponent) % into<number_t>;
static_assert(std::same_as<decltype(number)::result_type, number_t>);



inline namespace string_impl
{

	constexpr auto hex = ("u"_lit >> digit >> digit >> digit >> digit) % join;
	constexpr auto control = "\"/\\bfnrt"_one | hex;

	constexpr auto valid_char = not_<"\"\\"> | ((lit<'\\'> >> control) % join);

}

constexpr auto string = ign<'"'> >> join(*valid_char) >> ign<'"'>;
static_assert(std::same_as<decltype(string)::result_type, std::string_view>);



constexpr auto whitespace = *one<"\t\n\r "> % join;
static_assert(std::same_as<decltype(whitespace)::result_type, std::string_view>);



struct object_t;
struct array_t;
struct value_t;

using pair_t = std::pair<std::string_view, value_t>;

struct object_t
{
	object_t() = default;
	object_t(std::vector<pair_t>&& vec);
	std::map<std::string, value_t> data;
};
struct array_t
{
	array_t() = default;
	array_t(std::vector<value_t>&& vec);
	std::vector<value_t> data;
};
struct value_t
{
	std::variant<std::string, number_t, object_t, array_t, bool, nullptr_t> data;
};

object_t::object_t(std::vector<pair_t>&& vec)
{
	for (auto&& pair : std::move(vec))
		data.insert(pair);
}
array_t::array_t(std::vector<value_t>&& vec)
{
	for (auto&& pair : std::move(vec))
		data.push_back(pair);
}



struct JsonObjectParser : Custom<JsonObjectParser>
{
	using result_type = object_t;
	static consteval auto get_parser();
};
struct JsonArrayParser : Custom<JsonArrayParser>
{
	using result_type = array_t;
	static consteval auto get_parser();
};
struct JsonValueParser : Custom<JsonValueParser>
{
	using result_type = value_t;
	static consteval auto get_parser();
};

consteval auto JsonObjectParser::get_parser()
{
	constexpr auto pair = (ignore(whitespace) >> string >> ignore(whitespace) >> ":"_ign >> JsonValueParser{}) % into<pair_t>;
	constexpr auto object = delimit(pair, ","_lit) % into<object_t>;
	constexpr auto the_parser = "{"_ign >> (object | (whitespace % defaulted<object_t>)) >> "}"_ign;
	return the_parser;
}

consteval auto JsonArrayParser::get_parser()
{
	constexpr auto values = delimit(JsonValueParser{}, ","_lit) % into<array_t>;
	constexpr auto the_parser = "["_ign >> (values | (whitespace % defaulted<array_t>)) >> "]"_ign;
	return the_parser;
}

consteval auto JsonValueParser::get_parser()
{
	constexpr auto value_parser = into_choice<value_t>
	(
		string % into<std::string>,
		number,
		JsonObjectParser{},
		JsonArrayParser{},
		"true"_lit  % constant<true>,
		"false"_lit % constant<false>,
		"null"_lit  % constant<nullptr>
	);

	return ignore(whitespace) >> value_parser >> ignore(whitespace);
}



TOK3N_END_NAMESPACE(examples::json_parser)
