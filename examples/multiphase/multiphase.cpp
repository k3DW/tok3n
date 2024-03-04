#include <k3/tok3n.h>
#include <iostream>

using namespace k3::tok3n::operators;



struct StringView
{
    constexpr StringView(std::string_view sv)
        : data(sv.data()), size(sv.size()) {}

    template <std::size_t N>
    constexpr StringView(const char(&arr)[N])
        : data(arr), size(N) {}

    const char* data;
    std::size_t size;
};

enum class TokenKind
{
    whitespace,
	identifier,
    semicolon,
    colon,
    quote,

    lbrace,
    rbrace,
    lparen,
    rparen,

    plus,
    minus,
    star,
    slash,
    dot,

    equal,
    greater,
    less,
    exclamation,
};

struct Token
{
    StringView sv;
    TokenKind kind;
};



template <TokenKind kind>
constexpr auto into_token = fn<[](std::string_view sv) { return Token{ sv, kind }; }>;

int main()
{
    constexpr auto _lowercase = "abcdefghijklmnopqrstuvwxyz"_any_of;
    constexpr auto _uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"_any_of;
    constexpr auto _letter = _lowercase | _uppercase | "_"_any_of;
    constexpr auto _digit = "0123456789"_any_of;



    constexpr auto whitespace = join(+" \t\r\n"_any_of) % into_token<TokenKind::whitespace>;
    constexpr auto identifier = join(_letter >> *(_letter | _digit)) % into_token<TokenKind::identifier>;

    constexpr auto semicolon = ";"_any_of % into_token<TokenKind::semicolon>;
    constexpr auto colon     = ":"_any_of % into_token<TokenKind::colon>;
    constexpr auto quote     = "\""_any_of % into_token<TokenKind::quote>;

    constexpr auto lbrace = "{"_any_of % into_token<TokenKind::lbrace>;
    constexpr auto rbrace = "}"_any_of % into_token<TokenKind::rbrace>;
    constexpr auto lparen = "("_any_of % into_token<TokenKind::lparen>;
    constexpr auto rparen = ")"_any_of % into_token<TokenKind::rparen>;

    constexpr auto plus  = "+"_any_of % into_token<TokenKind::plus>;
    constexpr auto minus = "-"_any_of % into_token<TokenKind::minus>;
    constexpr auto star  = "*"_any_of % into_token<TokenKind::star>;
    constexpr auto slash = "/"_any_of % into_token<TokenKind::slash>;
    constexpr auto dot   = "."_any_of % into_token<TokenKind::dot>;

    constexpr auto equal       = "="_any_of % into_token<TokenKind::equal>;
    constexpr auto greater     = ">"_any_of % into_token<TokenKind::greater>;
    constexpr auto less        = "<"_any_of % into_token<TokenKind::less>;
    constexpr auto exclamation = "!"_any_of % into_token<TokenKind::exclamation>;



    constexpr auto single_token = whitespace
        | identifier
        | semicolon
        | colon
        | quote
        | lbrace
        | rbrace
        | lparen
        | rparen
        | plus
        | minus
        | star
        | slash
        | dot
        | equal
        | greater
        | less
        | exclamation
	;

    constexpr auto parser = *single_token % complete;

    constexpr auto input = R"(
		int main() { std::cout << "Hello World!"; return EXIT_SUCCESS; }
	)";

    auto result = parser.parse(input);




}
