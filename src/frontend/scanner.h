#ifndef LOX_SCANNER_H
#define LOX_SCANNER_H

#include "token.h"
#include <vector>

namespace Lox
{
    class Scanner
    {
    public:
        Scanner() = default;
        Scanner(std::string_view source);
        void reset(std::string_view source);
        [[nodiscard]] Token next_token();

    private:
        char advance();
        char peek() const;
        void new_line();

        bool is_at_end() const { return current_ >= source_.length(); }
        std::string_view current_substr() const { return source_.substr(token_start_, current_ - token_start_); }
        Token single_char_token(Token::Type type) const { return Token{.type = type, .string = current_substr(), .line = line_, .column = column_}; }
        Token eof_token() const { return Token{.type = Token::Type::Eof, .string = "", .line = line_, .column = column_}; }

        Token number_token();

    private:
        std::string_view source_;
        size_t current_ = 0;
        size_t line_ = 1;
        size_t column_ = 0;
        size_t token_start_ = 0;
    };
} // namespace Lox

#endif // LOX_SCANNER_H
