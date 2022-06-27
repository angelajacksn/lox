#ifndef LOX_STATEMENT_H
#define LOX_STATEMENT_H

#include "expression.h"

namespace Lox
{
    class PrintStmt;
    class ExpressionStmt;

    class StatementVisitor
    {
    public:
        virtual ~StatementVisitor() = default;
        virtual void visit(const PrintStmt& stmt) = 0;
        virtual void visit(const ExpressionStmt& stmt) = 0;
    };

    class Statement
    {
    public:
        using Ptr = std::unique_ptr<Statement>;
        template<typename StatementType, typename... Args>
            requires std::derived_from<StatementType, Statement>
        static auto create(Args&&... args)
        {
            return std::make_unique<StatementType>(std::forward<Args>(args)...);
        }

        virtual ~Statement() = default;
        virtual void accept(StatementVisitor& visitor) const = 0;
    };

    class PrintStmt : public Statement
    {
    public:
        PrintStmt(Expression::Ptr expression);
        void accept(StatementVisitor& visitor) const override { visitor.visit(*this); }
        const Expression& expression() const { return *expression_; }

    private:
        Expression::Ptr expression_;
    };

    class ExpressionStmt : public Statement
    {
    public:
        ExpressionStmt(Expression::Ptr expression);
        void accept(StatementVisitor& visitor) const override { visitor.visit(*this); }
        const Expression& expression() const { return *expression_; }

    private:
        Expression::Ptr expression_;
    };

} // namespace Lox

#endif // LOX_STATEMENT_H
