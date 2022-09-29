#include "pch.h"
#include <iostream>

void print(std::string_view str);
template <class... Ts>
void print(const std::tuple<Ts...>& tuple);
template <class T>
void print(const std::vector<T>& vector);
template <class T>
void print(const std::optional<T>& opt);
template <class T>
void print(const k3::tok3n::Result<T>& result);

void print(std::string_view str)
{
	std::cout << str;
}

template <class... Ts>
void print(const std::tuple<Ts...>& tuple)
{
	[&tuple]<std::size_t... Is>(std::index_sequence<Is...>)
	{
		(..., print(std::get<Is>(tuple)));
	}(std::index_sequence_for<Ts...>{});
}

template <class T>
void print(const std::vector<T>& vector)
{
	for (const auto& element : vector)
		print(element);
}

template <class T>
void print(const std::optional<T>& opt)
{
	if (opt.has_value())
		print(*opt);
}

template <class T>
void print(const k3::tok3n::Result<T>& result)
{
	if constexpr (std::same_as<T, void>)
	{
		if (result)
		{
			std::cout << "Lookahead parsed successfully";
			std::cout << "\nRemain: " << result.remaining() << "\n\n";
		}
		else
			std::cout << "Parse error\n\n";
	}
	else
	{
		if (result)
		{
			std::cout << "Parsed: ";
			print(result.value());
			std::cout << "\nRemain: " << result.remaining() << "\n\n";
		}
		else
			std::cout << "Parse error\n\n";
	}
}

#include "examples/json.h"

int main()
{
	using namespace k3;
	using namespace k3::tok3n;

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

	//auto json_result = json_parser::JsonValueParser::parse(R"( [  "test"  , true, -1234.5678e+90123 , [  "test"  , true, -1234.5678e+90123 , "" ]   ]      )");
	auto json_result = json_parser::JsonObjectParser::parse(json);

	volatile int x = 0;

	if (json_result)
	{
		auto& val = json_result.value();
		x += val.data.empty() ? 0 : 1;
	}
	else
		std::cout << "Json parse error!!!\n";




	constexpr auto lb = OneChar<"{">{};
	constexpr auto rb = OneChar<"}">{};

	constexpr auto a = OneChar<"a">{};
	constexpr auto b = OneChar<"b">{};

	constexpr auto ppppp = ignore(lb) >> a >> b >> ignore(rb);


	using PPPPP = Sequence<Ignore<OneChar<"{">>, OneChar<"a">, OneChar<"b">, Ignore<OneChar<"}">>>;
	static_assert(std::same_as<PPPPP, std::remove_cvref_t<decltype(ppppp)>>);

	using QQQQQ = Sequence<Ignore<OneChar<"{">>, OneChar<"a">, Ignore<OneChar<"}">>>;

	using RRRRR = PPPPP::result_type;


	//using SDSADAS = RRRRR::fdsfsdfsd;

	static_assert(std::same_as<PPPPP::result_type, std::tuple<std::string_view, std::string_view>>);
	static_assert(std::same_as<QQQQQ::result_type, std::string_view>);

	auto rrrr = PPPPP::parse("{ab}");
	auto rrrs = QQQQQ::parse("{a}");

}
