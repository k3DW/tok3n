// Copyright 2022-2024 Braden Ganetsky
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <k3/tok3n.h>
#include <map>
#include <variant>
#include <iostream>

using namespace k3::tok3n;

constexpr auto whitespace = *(" \n\r\t"_any) % ignore;



struct number_type
{
	std::string_view integer;
	std::optional<std::string_view> fraction;
	std::optional<std::string_view> exponent;
};

constexpr auto number = []
{
	constexpr auto digit = "0123456789"_any;

	constexpr auto natural_number = "0"_all | join("123456789"_any >> *digit);
	constexpr auto integer = (("-"_all | eps) >> natural_number) % join;

	constexpr auto fraction = ("."_ign >> +digit) % join;

	constexpr auto exponent = (ignore("Ee"_any) >> ("-+"_any | eps) >> +digit) % join;

	return (integer >> ~fraction >> ~exponent) % apply_into<number_type>;
}();



constexpr auto string = []
{
	constexpr auto hex = ("u"_all >> exactly<4>("0123456789ABCDEFabcdef"_any)) % join;
	constexpr auto control = R"("\/bfnrt)"_any | hex;
	
	constexpr auto valid_char = R"("\)"_none | join("\\"_all >> control);

	return ign<'"'> >> (*valid_char % join % into<std::string>) >> ign<'"'>;
}();



struct JsonValue : custom_parser<JsonValue>
{
	struct result_type;
	static consteval auto get_parser();
};

struct JsonObject : custom_parser<JsonObject>
{
	using result_type = std::vector<std::pair<std::string, JsonValue::result_type>>;
	static consteval auto get_parser();
};

struct JsonArray : custom_parser<JsonArray>
{
	using result_type = std::vector<JsonValue::result_type>;
	static consteval auto get_parser();
};

struct JsonValue::result_type
{
	using variant_type = std::variant<std::string, number_type, JsonObject::result_type, JsonArray::result_type, bool, std::nullptr_t>;
	variant_type variant;
};

consteval auto JsonObject::get_parser()
{
    constexpr auto pair = (whitespace >> string >> whitespace >> ":"_ign >> JsonValue{}) % apply_into<result_type::value_type>;
    constexpr auto object = pair % delimit(","_all);
    constexpr auto the_parser = "{"_ign >> (object | whitespace) >> "}"_ign;
    return the_parser;
}

consteval auto JsonArray::get_parser()
{
    constexpr auto values = JsonValue{} % delimit(","_all);
    constexpr auto the_parser = "["_ign >> (values | whitespace) >> "]"_ign;
    return the_parser;
}

consteval auto JsonValue::get_parser()
{
    constexpr auto value_parser =
        string |
        number |
        JsonObject{} |
        JsonArray{} |
        "true"_all  % constant<true> |
        "false"_all % constant<false> |
        "null"_all  % constant<nullptr>;

    return whitespace >> value_parser >> whitespace;
}



int main()
{

	constexpr std::string_view json =
		R"({
	"id": "0001",
	"type": "donut",
	"name": "Cake",
	"image":
		{
			"url": "images/0001.jpg",
			"width": 200,
			"height": 200
		},
	"thumbnail":
		{
			"url": "images/thumbnails/0001.jpg",
			"width": 32,
			"height": 32
		}
})";

	//auto result = number.parse("-1234.5678e+9012");
	auto result = string.parse(R"("-1234.5678e+9012tdtrwehfg)");

	//auto json_result = JsonValue::parse(R"( [  "test"  , true, -1234.5678e+90123 , [  "test"  , true, -1234.5678e+90123 , "" ]   ]      )");
	auto json_result = JsonObject::parse(json);

	if (json_result)
	{
		auto& val = json_result.value();
		std::ignore = val;
	}
	else
		std::cout << "Json parse error!!!\n";

}
