#include "parser.h"

namespace Lox
{
    void Parser::reset(std::string_view source)
    {
        *this = Parser(source);
    }

    std::vector<Statement::Ptr> Parser::parse()
    {
        try {
            advance();
            std::vector<Statement::Ptr> statements;
            while (current_token_.type != Token::Type::Eof) {
                statements.push_back(statement());
            }
            return statements;
        } catch (const SyntaxError& e) {
            fmt::print(stderr, "SyntaxError: {}\n", e.what());
            had_error_ = true;
        }
        return {};
    }

    Statement::Ptr Parser::statement()
    {
        if (match(Token::Type::Print))
            return print_statement();
        return expression_statement();
    }

    Statement::Ptr Parser::print_statement()
    {
        auto expr = expression();
        expect_and_consume(Token::Type::Semicolon, "Expected ';' after value");
        return Statement::create<PrintStmt>(std::move(expr));
    }

    Statement::Ptr Parser::expression_statement()
    {
        auto expr = expression();
        expect_and_consume(Token::Type::Semicolon, "Expected ';' after expression");
        return Statement::create<ExpressionStmt>(std::move(expr));
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
        while (match(Token::Type::Star, Token::Type::Slash, Token::Type::Modulus)) {
            auto binary_operator = previous_token_;
            expr = Expression::create<BinaryExpr>(std::move(expr), binary_operator, unary());
        }
        return expr;
    }

    Expression::Ptr Parser::unary()
    {
        if (match(Token::Type::Minus)) {
            auto unary_operator = previous_token_;
            return Expression::create<UnaryExpr>(unary(), unary_operator);
        }
        return primary();
    }

    Expression::Ptr Parser::primary()
    {
        if (match(Token::Type::Number))
            return Expression::create<LiteralExpr>(Object::create<Number>(previous_token_.string), previous_token_.location);
        else if (match(Token::Type::String))
            return Expression::create<LiteralExpr>(Object::create<String>(previous_token_.string), previous_token_.location);
        else if (match(Token::Type::LeftParen)) {
            auto expr = expression();
            expect_and_consume(Token::Type::RightParen, "Expected ')' after expression");
            return Expression::create<GroupingExpr>(std::move(expr));
        }
        throw syntax_error("Invalid syntax");
    }

    Token& Parser::advance()
    {
        previous_token_ = current_token_;
        current_token_ = scanner_.next_token();
        return current_token_;
    }

    void Parser::expect_and_consume(Token::Type type, const std::string& error_message)
    {
        if (!match(type))
            throw SyntaxError(error_message, current_token_.location);
    }

    SyntaxError Parser::syntax_error(const std::string& message) const
    {
        return {message, current_token_.location};
    }
} // namespace Lox