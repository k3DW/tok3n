#include "parsers/parsers.h"
#include "operators/operators.h"

#include <iostream>
#if 1

void print(std::string_view str);
template <class... Ts>
void print(const std::tuple<Ts...>& tuple);
template <class T>
void print(const std::vector<T>& vector);
template <class T>
void print(const std::optional<T>& opt);
template <class T>
void print(const k3::parser::Result<T>& result);

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
void print(const k3::parser::Result<T>& result)
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

namespace k3::parser
{
	/*
	namespace Json
	{

		// JSON "number" parsing

		constexpr IsOneChar auto minus = OneChar<'-'>{};
		constexpr IsOneChar auto signs = OneChar<"+-">{};
		constexpr IsOneChar auto zero = OneChar<'0'>{};
		constexpr IsOneChar auto point = OneChar<'.'>{};
		constexpr IsOneChar auto digit = OneChar<"0123456789">{};
		constexpr IsOneChar auto nonzerodigit = OneChar<"123456789">{};
		constexpr IsOneChar auto Ee = OneChar<"Ee">{};

		constexpr IsSequence auto integer = (~minus) >> (zero | (nonzerodigit >> *digit));

		constexpr IsSequence auto fraction = point >> +digit;

		constexpr IsSequence auto exponent = Ee >> ~signs >> +digit;

		constexpr IsSequence auto number = integer >> ~fraction >> ~exponent;

		// JSON "whitespace" parsing

		constexpr IsZeroOrMore auto whitespace = *OneChar<"\t\n\r ">{};

		// JSON "string" parsing

		constexpr IsOneChar auto quote = OneChar<'"'>{};
		constexpr IsOneChar auto backslash = OneChar<'\\'>{};

		constexpr auto hex = OneChar<'u'>{} >> digit >> digit >> digit >> digit;
		constexpr auto control = OneChar<"\"/\\bfnrt">{} | hex;

		constexpr auto valid_char = !(quote | backslash) | (backslash >> control);

		constexpr auto string = quote >> *valid_char >> quote;



		constexpr IsOneChar auto comma = OneChar<','>{};
		constexpr IsOneChar auto colon = OneChar<':'>{};
		constexpr IsOneChar auto left_brace = OneChar<'{'>{};
		constexpr IsOneChar auto right_brace = OneChar<'}'>{};
		constexpr IsOneChar auto left_bracket = OneChar<'['>{};
		constexpr IsOneChar auto right_bracket = OneChar<']'>{};

		struct JsonObjectParser;
		struct JsonArrayParser;
		struct JsonValueParser;

	}

	template <>
	constexpr ParserType parser_type_v<Json::JsonObjectParser> = ParserType{ 100 };
	template <>
	constexpr ParserType parser_type_v<Json::JsonArrayParser> = ParserType{ 100 };
	template <>
	constexpr ParserType parser_type_v<Json::JsonValueParser> = ParserType{ 100 };

	namespace Json
	{
		/*
		struct JsonObjectParser
		{
			static constexpr Result parse(Input input);
		};
		struct JsonArrayParser
		{
			static constexpr Result parse(Input input);
		};
		struct JsonValueParser
		{
			static constexpr Result parse(Input input);
		};

		constexpr Result JsonObjectParser::parse(Input input)
		{
			constexpr auto pair = whitespace >> string >> whitespace >> colon >> JsonValueParser{};
			constexpr auto pairs = pair >> *(comma >> pair);
			constexpr auto the_parser = left_brace >> (pairs | whitespace) >> right_brace;

			return the_parser.parse(input);
		}
		constexpr Result JsonArrayParser::parse(Input input)
		{
			constexpr auto values = JsonValueParser{} >> *(comma >> JsonValueParser{});
			constexpr auto the_parser = left_bracket >> (values | whitespace) >> right_bracket;

			return the_parser.parse(input);
		}
		constexpr Result JsonValueParser::parse(Input input)
		{
			constexpr auto value = string | number | JsonObjectParser{} | JsonArrayParser{} | Literal<"true">{} | Literal<"false">{} | Literal<"null">{};
			constexpr auto the_parser = whitespace >> value >> whitespace;

			return the_parser.parse(input);
		}

	}
	*/


}

int main()
{
	using namespace k3;
	using namespace k3::parser;


	using OCA = OneChar<'a'>;
	using OCB = OneChar<'b'>;
	using OCC = OneChar<'c'>;

	print(OCA::parse("abc"));
	print(OCB::parse("abc"));

	print(Choice<OCA, OCB, OCC>::parse("bx"));

	std::cout << "\n\n";



	constexpr static_string sdfjksdnf = "asfnjaksd";

	OneChar<"ab"> test;
	OneChar<"ac"> test2;

	auto dkfjsdkf = test | test2;
	static_assert(std::same_as<OneChar<"abc">, decltype(dkfjsdkf)>);

	OneChar<'d'> test3;

	constexpr Choice<OneChar<'a'>, OneChar<'b'>> c1;
	constexpr Choice<OneChar<'c'>, OneChar<'d'>> c2;

	constexpr OneChar<'e'> oc;

	auto c3a = c1 | c2;
	static_assert(std::same_as<Choice<OneChar<'a'>, OneChar<'b'>, OneChar<'c'>, OneChar<'d'>>, decltype(c3a)>);
	auto c3b = c2 | c1;
	static_assert(std::same_as<Choice<OneChar<'c'>, OneChar<'d'>, OneChar<'a'>, OneChar<'b'>>, decltype(c3b)>);

	auto c4a = c1 | oc;
	static_assert(std::same_as<Choice<OneChar<'a'>, OneChar<'b'>, OneChar<'e'>>, decltype(c4a)>);
	auto c4b = oc | c1;
	static_assert(std::same_as<Choice<OneChar<'e'>, OneChar<'a'>, OneChar<'b'>>, decltype(c4b)>);

	auto c5a = c2 | oc;
	static_assert(std::same_as<Choice<OneChar<'c'>, OneChar<'d'>, OneChar<'e'>>, decltype(c5a)>);
	auto c5b = oc | c2;
	static_assert(std::same_as<Choice<OneChar<'e'>, OneChar<'c'>, OneChar<'d'>>, decltype(c5b)>);


	Sequence<OneChar<"abc">, OneChar<"bcd">> seq;
	auto seq2 = seq >> seq;

	print(seq2.parse("abcd"));

	using SEQ1 = Sequence<OneChar<"ab">, OneChar<"bc">>;
	static_assert(std::same_as<decltype(std::declval<SEQ1>() >> std::declval<SEQ1>()), Sequence<OneChar<"ab">, OneChar<"bc">, OneChar<"ab">, OneChar<"bc">>>);


	using OC01 = OneChar<"abc">;
	using OC02 = OneChar<'b'>;
	auto oc01 = OC01{};
	auto oc02 = OC02{};

	using SEQ02 = Sequence<OC01, OC02>;
	auto seq02 = oc01 >> oc02;
	static_assert(std::same_as<SEQ02, decltype(seq02)>);

	using OOM01 = OneOrMore<SEQ02>;
	auto oom01 = +seq02;
	static_assert(std::same_as<OOM01, decltype(oom01)>);
	static_assert(std::same_as<decltype(oom01), decltype(+oom01)>);
	static_assert(std::same_as<decltype(oom01), decltype(+ +oom01)>);
	static_assert(std::same_as<decltype(oom01), decltype(+ + +oom01)>);

	using ZOM01 = ZeroOrMore<SEQ02>;
	auto zom01 = *seq02;
	static_assert(std::same_as<ZOM01, decltype(zom01)>);
	static_assert(std::same_as<decltype(zom01), decltype(*zom01)>);
	static_assert(std::same_as<decltype(zom01), decltype(**zom01)>);
	static_assert(std::same_as<decltype(zom01), decltype(***zom01)>);

	static_assert(std::same_as<ZOM01, decltype(*oom01)>);
	static_assert(std::same_as<ZOM01, decltype(+zom01)>);
	static_assert(std::same_as<ZOM01, decltype(+*oom01)>);
	static_assert(std::same_as<ZOM01, decltype(*+zom01)>);

	std::cout << "\n";
	print(zom01.parse("aabbbcbbaba"));
	std::cout << "\n";
	print(zom01.parse("abbbcbbaba"));

	using ZOO01 = ZeroOrOne<SEQ02>;
	auto zoo01 = ~seq02;
	std::cout << "\n";
	print(zoo01.parse("abbb"));
	std::cout << "\n";
	print(zoo01.parse("aabb"));

	static_assert(std::same_as<ZOO01, decltype(zoo01)>);
	static_assert(std::same_as<ZOO01, decltype(~zoo01)>);
	static_assert(std::same_as<ZOO01, decltype(~~zoo01)>);
	static_assert(std::same_as<ZOO01, decltype(~~~zoo01)>);

	static_assert(std::same_as<ZOM01, decltype(+zoo01)>);
	static_assert(std::same_as<ZOM01, decltype(*zoo01)>);
	static_assert(std::same_as<ZOM01, decltype(~oom01)>);
	static_assert(std::same_as<ZOM01, decltype(~zom01)>);

	std::cout << "\n\n";

	{
		/*
		using namespace Json;
		
		Result res = number.parse("-14324.124e+42this is now the end");
		print(res);

		Result res2 = string.parse(R"("this is a "test string)");
		print(res2);
		
		Result res3 = string.parse(R"("this is another t"est" strin"g")");
		print(res3);
		*/
	}


	static_assert(std::same_as<decltype(zoo01 | zoo01), ZOO01>);



	using OC10 = OneChar<"abc">;
	using NC10 = NotChar<"abc">;
	using NC11 = NotChar<"d">;
	using NC12 = NotChar<"bcd">;

	constexpr OC10 oc10;
	constexpr NC10 nc10;
	constexpr NC11 nc11;
	constexpr NC12 nc12;

	static_assert(std::same_as<decltype(!oc10), NC10>);
	static_assert(std::same_as<decltype(!nc10), OC10>);
	static_assert(std::same_as<decltype(!!nc10), NC10>);
	static_assert(std::same_as<decltype(!!oc10), OC10>);

	static_assert(std::same_as<decltype(nc10 | nc10), NC10>);
	static_assert(std::same_as<decltype(nc11 | nc11), NC11>);
	static_assert(std::same_as<decltype(nc10 | nc11), OneChar<every_char>>);
	static_assert(std::same_as<decltype(nc11 | nc10), OneChar<every_char>>);

	static_assert(std::same_as<decltype(nc10 | oc10), OneChar<every_char>>);
	static_assert(std::same_as<decltype(oc10 | nc10), OneChar<every_char>>);
	static_assert(std::same_as<decltype(nc11 | oc10), NC11>);
	static_assert(std::same_as<decltype(oc10 | nc11), NC11>);
	static_assert(std::same_as<decltype(nc12 | oc10), NotChar<'d'>>);
	static_assert(std::same_as<decltype(oc10 | nc12), NotChar<'d'>>);

	print(NC10::parse("d"));
	print(NC10::parse("a"));
	print(NC10::parse("+"));



	using L01 = Literal<"test">;
	using L02 = Literal<"1234">;

	constexpr L01 l01;
	constexpr L02 l02;

	static_assert(std::same_as<decltype(l01 >> l01), Literal<"testtest">>);
	static_assert(std::same_as<decltype(l01 >> l02), Literal<"test1234">>);
	static_assert(std::same_as<decltype(l02 >> l01), Literal<"1234test">>);
	static_assert(std::same_as<decltype(l02 >> l02), Literal<"12341234">>);


	/*
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

	Result json_result = Json::JsonObjectParser::parse(json);
	if (json_result)
		std::cout << json_result.flatten() << "\n";
	else
		std::cout << "Json parse error!!!\n";
	*/

}
#endif