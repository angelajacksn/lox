#include "parser.h"

namespace Lox
{
    void Parser::reset(std::string_view source)
    {
        *this = Parser(source);
    }

    Expression::Ptr Parser::parse()
    {
        try {
            advance();
            return expression();
        }
        catch (const SyntaxError& e) {
            fmt::print(stderr, "SyntaxError: {}\n", e.what());
            had_error_ = true;
        }
        return nullptr;
    }

    Expression::Ptr Parser::expression()
    {
        return add_subtract();
    }

    Expression::Ptr Parser::add_subtract()
    {
        auto expr = factor();
        while (match(Token::Type::Plus, Token::Type::Minus)) {
            auto binary_operator = previous_token_;
            expr = Expression::create<BinaryExpr>(std::move(expr), binary_operator, factor());
        }
        return expr;
    }

    Expression::Ptr Parser::factor()
    {
        auto expr = unary();
        while (match(Token::Type::Star, Token::Type::Slash)) {
            auto binary_operator = previous_token_;
            expr = Expression::create<BinaryExpr>(std::move(expr), binary_operator, unary());
        }
        return expr;
    }

    Expression::Ptr Parser::unary()
    {
        if (match(Token::Type::Minus)) {
            return Expression::create<UnaryExpr>(unary(), previous_token_);
        }
        return primary();
    }

    Expression::Ptr Parser::primary()
    {
        if (match(Token::Type::Number))
            return Expression::create<LiteralExpr>(Object::create<Number>(previous_token_.string));
        else if (match(Token::Type::LeftParen)) {
            auto expr = expression();
            expect_and_consume(Token::Type::RightParen, "Expected ')' after expression");
            return Expression::create<GroupingExpr>(std::move(expr));
        }
        throw syntax_error("Invalid syntax");
    }

    Token& Parser::advance()
    {
        previous_token_ = std::move(current_token_);
        current_token_ = scanner_.next_token();
        return current_token_;
    }

    void Parser::expect_and_consume(Token::Type type, const std::string& error_message)
    {
        if (!match(type)) {

        }
    }

    SyntaxError Parser::syntax_error(const std::string& message)
    {
        return SyntaxError(message, current_token_.line, current_token_.column);
    }
} // namespace Lox