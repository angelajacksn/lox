#ifndef LOX_TOKEN_H
#define LOX_TOKEN_H

#include "common/source_location.h"
#include <fmt/format.h>
#include <string>
#include <string_view>

namespace Lox
{
    struct Token {
        enum class Type {
            Number,

            Plus,
            Minus,
            Star,
            Slash,
            LeftParen,
            RightParen,
            Semicolon,
            Modulus,

            Identifier,
            Print,

            Eof
        };

        Token::Type type;
        std::string_view string;
        SourceLocation location;
    };

    constexpr std::string to_string(Token::Type type)
    {
        using enum Token::Type;
        switch (type) {
            case Number:
                return "NUMBER";
            case Plus:
                return "PLUS";
            case Minus:
                return "MINUS";
            case Star:
                return "STAR";
            case Slash:
                return "SLASH";
            case LeftParen:
                return "LEFT_PAREN";
            case RightParen:
                return "RIGHT_PAREN";
            case Semicolon:
                return "SEMICOLON";
            case Modulus:
                return "MODULUS";
            case Identifier:
                return "IDENTIFIER";
            case Print:
                return "PRINT";
            case Eof:
                return "EOF";
        }
        return "UNKNOWN";
    }
} // namespace Lox

template<>
struct fmt::formatter<Lox::Token> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const Lox::Token& token, FormatContext& ctx) const -> decltype(ctx.out())
    {
        return format_to(ctx.out(), "{}: {{ str: {}, line: {}, column: {} }}",
                         Lox::to_string(token.type),
                         token.string,
                         token.location.line,
                         token.location.column);
    }
};

#endif // LOX_TOKEN_H
