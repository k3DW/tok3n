#include <k3/tok3n.h>
#include <iostream>

using namespace k3::tok3n::operators;



enum class TokenKind
{
    whitespace,
	identifier,
    semicolon,
    double_colon,
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
    std::string_view sv;
    TokenKind kind;
};

constexpr bool operator==(TokenKind lhs, const Token& rhs)
{
    return lhs == rhs.kind;
}



template <TokenKind kind>
constexpr auto into_token = fn<[](std::string_view sv) { return Token{ sv, kind }; }>;

constexpr auto single_token = []
{
    constexpr auto _lowercase = "abcdefghijklmnopqrstuvwxyz"_any_of;
    constexpr auto _uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"_any_of;
    constexpr auto _letter = _lowercase | _uppercase | "_"_any_of;
    constexpr auto _digit = "0123456789"_any_of;

    constexpr auto whitespace = join(+" \t\r\n"_any_of) % into_token<TokenKind::whitespace>;
    constexpr auto identifier = join(_letter >> *(_letter | _digit)) % into_token<TokenKind::identifier>;
    
    constexpr auto semicolon    = ";"_any_of % into_token<TokenKind::semicolon>;
    constexpr auto double_colon = "::"_all_of % into_token<TokenKind::double_colon>;
    constexpr auto colon        = ":"_any_of % into_token<TokenKind::colon>;
    constexpr auto quote        = "\""_any_of % into_token<TokenKind::quote>;
    
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

    return whitespace
        | identifier
        | semicolon
        | double_colon
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
}();

constexpr auto tokenizer = *single_token % complete;




int main()
{
    constexpr auto input = R"(
		int main() { std::cout << "Hello World!"; return EXIT_SUCCESS; }
	)";
    
    auto result = tokenizer.parse(input);
    
    for (auto it = result.value().begin(); it != result.value().end(); )
    {
        if (it->kind == TokenKind::whitespace)
            it = result.value().erase(it);
        else
            ++it;
    }



    auto name = (all_of<TokenKind::identifier> >> *all_of<TokenKind::double_colon, TokenKind::identifier>)
		% apply<[](Token tok, const std::vector<Token>& tokens)
		{
            std::string str;
            str.append(tok.sv);
            for (auto& token : tokens)
                str.append(token.sv);
            return str;
		}>;


    //auto ppp = name | k3::tok3n::anything<TokenKind>;


    //auto temp = *all_of<TokenKind::double_colon, TokenKind::identifier>;
    //
    //std::span<const Token> input2{ result.value().data(), result.value().size() };
    //
    ////std::vector<TokenKind> tempvec;
    ////tempvec.push_back(TokenKind::identifier);
    ////tempvec.push_back(TokenKind::identifier);
    ////
    ////
    ////k3::tok3n::Input<TokenKind> input3{ tempvec.data(), tempvec.size() };
    //
    //auto result2 = temp.parse(k3::tok3n::Input<Token>(input2));



    


}
