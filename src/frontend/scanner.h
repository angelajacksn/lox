#ifndef LOX_SCANNER_H
#define LOX_SCANNER_H

#include "token.h"
#include <vector>
#include <unordered_map>

namespace Lox
{
    class Scanner
    {
    public:
        Scanner() = default;
        Scanner(std::string_view source);
        void reset(std::string_view source);
        [[nodiscard]] Token next_token();

        // TODO: Maybe get rid of the static/global
        static const std::unordered_map<std::string_view, Token::Type> kKeywords;

    private:
        char advance();
        char peek() const;

        bool is_at_end() const { return current_ >= source_.length(); }
        std::string_view current_substr() const { return source_.substr(token_start_, current_ - token_start_); }
        Token single_char_token(Token::Type type) const
        {
            return Token{.type = type, .string = current_substr(), .location = location_};
        }
        Token eof_token() const { return Token{.type = Token::Type::Eof, .string = "", .location = location_}; }

        Token number_token();
        Token identifier_or_keyword();
        Token string_token();

    private:
        std::string_view source_;
        size_t current_ = 0;
        size_t token_start_ = 0;
        SourceLocation location_;
    };
} // namespace Lox

#endif // LOX_SCANNER_H
