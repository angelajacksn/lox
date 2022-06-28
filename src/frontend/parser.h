#ifndef LOX_PARSER_H
#define LOX_PARSER_H

#include "AST/expression.h"
#include "AST/statement.h"
#include "scanner.h"
#include "syntax_error.h"
#include <vector>

namespace Lox
{
    class Parser
    {
    public:
        Parser() = default;
        Parser(std::string_view source)
            : scanner_(source)
        {
        }

        void reset(std::string_view source);
        std::vector<Statement::Ptr> parse();
        bool had_error() const { return had_error_; }

    private:
        Statement::Ptr statement();
        Statement::Ptr print_statement();
        Statement::Ptr expression_statement();
        Expression::Ptr expression();
        Expression::Ptr equality();
        Expression::Ptr add_subtract();
        Expression::Ptr factor();
        Expression::Ptr unary();
        Expression::Ptr primary();

        Token& advance();
        void expect_and_consume(Token::Type type, const std::string& error_message);
        SyntaxError syntax_error(const std::string& message) const;

        bool check(Token::Type type) const { return current_token_.type == type; }
        template<typename... Types>
        bool match(Types... types)
        {
            if ((check(types) || ...)) {
                advance();
                return true;
            }
            return false;
        }

    private:
        Scanner scanner_;
        Token previous_token_;
        Token current_token_;
        bool had_error_ = false;
    };
} // namespace Lox

#endif // LOX_PARSER_H
