#include "scanner.h"

#include "syntax_error.h"

namespace Lox
{
    Scanner::Scanner(std::string_view source)
        : source_(source)
    {
    }

    void Scanner::reset(std::string_view source)
    {
        *this = Scanner(source);
    }

    Token Scanner::next_token()
    {
        while (!is_at_end()) {
            token_start_ = current_;
            switch (char c = advance()) {
                case '\t':
                case '\r':
                case ' ':
                    break;
                case '\n':
                    new_line();
                    break;
                case '+':
                    return single_char_token(Token::Type::Plus);
                case '-':
                    return single_char_token(Token::Type::Minus);
                case '*':
                    return single_char_token(Token::Type::Star);
                case '/':
                    return single_char_token(Token::Type::Slash);
                case '(':
                    return single_char_token(Token::Type::LeftParen);
                case ')':
                    return single_char_token(Token::Type::RightParen);
                default:
                    if (std::isdigit(c))
                        return number_token();
                    throw SyntaxError("Unknown character", line_, column_);
            }
        }
        return eof_token();
    }

    char Scanner::advance()
    {
        ++column_;
        return source_.at(current_++);
    }

    void Scanner::new_line()
    {
        ++line_;
        column_ = 0;
    }

    Token Scanner::number_token()
    {
        auto number_start_column = column_;
        auto consume_number = [this] {
            while (!is_at_end() && std::isdigit(peek()))
                advance();
        };

        consume_number();
        if (peek() == '.') {
            advance();
            if (!std::isdigit(peek()))
                throw SyntaxError("Invalid floating point syntax. Expected number after '.'", line_, column_);
            consume_number();
        }
        return Token{.type = Token::Type::Number, .string = current_substr(), .line = line_, .column = number_start_column};
    }
} // namespace Lox