#pragma once
#include <k3/tok3n.h>
#include <map>
#include <variant>
#include <charconv>

TOK3N_BEGIN_NAMESPACE(examples::json_parser)



constexpr auto whitespace = *("\t\n\r "_one) % ignore;



struct number_type
{
	std::string_view integer;
	std::optional<std::string_view> fraction;
	std::optional<std::string_view> exponent;
};

constexpr auto number = []
{
	constexpr auto digit = "0123456789"_one;

	constexpr auto natural_number = "0"_lit | join("123456789"_one >> *digit);
	constexpr auto integer = (~"-"_lit >> natural_number) % join;

	constexpr auto fraction = ("."_ign >> +digit) % join;

	constexpr auto exponent = (ignore("Ee"_one) >> ~"+-"_one >> +digit) % join;

	return (integer >> ~fraction >> ~exponent) % apply_into<number_type>;
}();


constexpr auto string = []
{
	constexpr auto hex = ("u"_lit >> exactly<4>("0123456789ABCDEFabcdef"_one)) % join;
	constexpr auto control = R"("/\bfnrt)"_one | hex;
	
	constexpr auto valid_char = R"("\)"_not | join("\\"_lit >> control);

	return ign<'"'> >> (*valid_char % join % into<std::string>) >> ign<'"'>;
}();



struct JsonValue : Custom<JsonValue>
{
	struct result_type;
	static consteval auto get_parser();
};

struct JsonObject : Custom<JsonObject>
{
	using result_type = std::vector<std::pair<std::string, JsonValue::result_type>>;
	static consteval auto get_parser();
};

struct JsonArray : Custom<JsonArray>
{
	using result_type = std::vector<JsonValue::result_type>;
	static consteval auto get_parser();
};

struct JsonValue::result_type
{
	using variant_type = std::variant<std::string, number_type, JsonObject::result_type, JsonArray::result_type, bool, nullptr_t>;
	variant_type variant;
};

consteval auto JsonObject::get_parser()
{
    constexpr auto pair = (whitespace >> string >> whitespace >> ":"_ign >> JsonValue{}) % apply_into<result_type::value_type>;
    constexpr auto object = pair % delimit(","_lit);
    constexpr auto the_parser = "{"_ign >> (object | (whitespace % defaulted<result_type>)) >> "}"_ign;
    return the_parser;
}

consteval auto JsonArray::get_parser()
{
    constexpr auto values = JsonValue{} % delimit(","_lit);
    constexpr auto the_parser = "["_ign >> (values | (whitespace % defaulted<result_type>)) >> "]"_ign;
    return the_parser;
}

consteval auto JsonValue::get_parser()
{
    constexpr auto value_parser = into_choice<result_type>
    (
        string,
        number,
        JsonObject{},
        JsonArray{},
        "true"_lit  % constant<true>,
        "false"_lit % constant<false>,
        "null"_lit  % constant<nullptr>
    );

    return whitespace >> value_parser >> whitespace;
}



TOK3N_END_NAMESPACE(examples::json_parser)



#include <iostream>

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

	using namespace k3::tok3n::examples;

	//auto result = json_parser::number.parse("-1234.5678e+9012");
	auto result = json_parser::string.parse(R"("-1234.5678e+9012tdtrwehfg)");

	//auto json_result = json_parser::JsonValue::parse(R"( [  "test"  , true, -1234.5678e+90123 , [  "test"  , true, -1234.5678e+90123 , "" ]   ]      )");
	auto json_result = json_parser::JsonObject::parse(json);

	volatile int x = 0;

	if (json_result)
	{
		auto& val = json_result.value();
		x += val.empty() ? 0 : 1;
	}
	else
		std::cout << "Json parse error!!!\n";

}
