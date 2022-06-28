#include "scanner.h"

#include "syntax_error.h"

namespace Lox
{
    const std::unordered_map<std::string_view, Token::Type> Scanner::kKeywords = {
        {"print", Token::Type::Print},
        {"true", Token::Type::True},
        {"false", Token::Type::False},
    };

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
                case ';':
                    return single_char_token(Token::Type::Semicolon);
                case '%':
                    return single_char_token(Token::Type::Modulus);
                case '=':
                    return single_char_token(match('=') ? Token::Type::EqualEqual : Token::Type::Equal);
                case '!':
                    return single_char_token(match('=') ? Token::Type::BangEqual : Token::Type::Bang);
                case '"':
                    return string_token();
                default:
                    if (std::isalpha(c) || c == '_')
                        return identifier_or_keyword();
                    else if (std::isdigit(c))
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

    Token Scanner::identifier_or_keyword()
    {
        auto start_location = location_;
        for (char c = advance(); std::isalnum(c) || c == '_'; c = peek())
            advance();

        auto token_type = Token::Type::Identifier;
        auto string = current_substr();
        auto it = kKeywords.find(string);
        if (it != kKeywords.end())
            token_type = it->second;
        return Token{.type = token_type, .string = string, .location = start_location};
    }

    Token Scanner::string_token()
    {
        auto start_location = location_;
        auto throw_if_at_end = [this, start_location] {
            if (is_at_end())
                throw SyntaxError("Unterminated string", start_location);
        };

        // Syntax error if opening '"' is the last character in source
        throw_if_at_end();
        // '"";'
        for (char c = advance(); !is_at_end() && c != '"'; c = peek()) {
            if (c == '\n')
                location_.new_line();
            advance();
        }
        // Syntax error if we reached the end without a closing '"'
        throw_if_at_end();

        if (peek() == '"')
            advance(); // Consume closing '"'

        // Explicitly calling source.substr rather
        // than current_substr() since we need to discard the starting and closing '"'
        return Token{
            .type = Token::Type::String,
            .string = source_.substr(token_start_ + 1, current_ - (token_start_ + 1) - 1),
            .location = start_location};
    }
} // namespace Lox