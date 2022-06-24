#ifndef LOX_TOKEN_H
#define LOX_TOKEN_H

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

            Eof
        };

        Token::Type type;
        std::string_view string;
        size_t line;
        size_t column;
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
                         token.line,
                         token.column);
    }
};

#endif // LOX_TOKEN_H