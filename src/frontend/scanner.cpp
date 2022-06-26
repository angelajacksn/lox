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
                    location_.new_line();
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
                    throw SyntaxError("Unknown character", location_);
            }
        }
        return eof_token();
    }

    char Scanner::advance()
    {
        location_.advance();
        return source_.at(current_++);
    }

    char Scanner::peek() const
    {
        if (is_at_end())
            return '\0';
        return source_.at(current_);
    }

    Token Scanner::number_token()
    {
        auto number_start_location = location_;
        auto consume_number = [this] {
            while (!is_at_end() && std::isdigit(peek()))
                advance();
        };

        consume_number();
        if (peek() == '.') {
            advance();
            if (!std::isdigit(peek()))
                throw SyntaxError("Invalid floating point syntax. Expected number after '.'", location_);
            consume_number();
        }
        return Token{.type = Token::Type::Number, .string = current_substr(), .location = number_start_location};
    }
} // namespace Lox