#ifndef LOX_EXPRESSION_H
#define LOX_EXPRESSION_H

#include "common/object.h"
#include "frontend/token.h"

#include <memory>

namespace Lox
{
    class BinaryExpr;
    class UnaryExpr;
    class LiteralExpr;
    class GroupingExpr;

    class ExpressionVisitor
    {
    public:
        virtual ~ExpressionVisitor() = default;
        virtual Object::Ptr visit(const BinaryExpr& expr) = 0;
        virtual Object::Ptr visit(const UnaryExpr& expr) = 0;
        virtual Object::Ptr visit(const LiteralExpr& expr) = 0;
        virtual Object::Ptr visit(const GroupingExpr& expr) = 0;
    };

    class Expression
    {
    public:
        using Ptr = std::unique_ptr<Expression>;
        template<typename ExpressionType, typename... Args>
            requires std::derived_from<ExpressionType, Expression>
        static auto create(Args&&... args)
        {
            return std::make_unique<ExpressionType>(std::forward<Args>(args)...);
        }

        virtual ~Expression() = default;
        virtual Object::Ptr accept(ExpressionVisitor& visitor) const = 0;
    };

    class BinaryExpr : public Expression
    {
    public:
        BinaryExpr(Expression::Ptr left, Token binary_operator, Expression::Ptr right);
        Object::Ptr accept(ExpressionVisitor& visitor) const override
        {
            return visitor.visit(*this);
        }

        const Expression& left() const { return *left_; }
        const Token& binary_operator() const { return operator_; }
        const Expression& right() const { return *right_; }

    private:
        Expression::Ptr left_;
        Token operator_;
        Expression::Ptr right_;
    };

    class UnaryExpr : public Expression
    {
    public:
        UnaryExpr(Expression::Ptr operand, Token unary_operator);
        Object::Ptr accept(ExpressionVisitor& visitor) const override
        {
            return visitor.visit(*this);
        }

        const Expression& operand() const { return *operand_; }
        const Token& unary_operator() const { return operator_; }

    private:
        Expression::Ptr operand_;
        Token operator_;
    };

    class LiteralExpr : public Expression
    {
    public:
        LiteralExpr(Object::Ptr value);
        Object::Ptr accept(ExpressionVisitor& visitor) const override
        {
            return visitor.visit(*this);
        }

        const Object& value() const { return *value_; }
        Object::Ptr share_object() const { return value_; }

    private:
        Object::Ptr value_;
    };

    class GroupingExpr : public Expression
    {
    public:
        GroupingExpr(Expression::Ptr expression);
        Object::Ptr accept(ExpressionVisitor& visitor) const override
        {
            return visitor.visit(*this);
        }
        const Expression& expression() const { return *expression_; }

    private:
        Expression::Ptr expression_;
    };
} // namespace Lox

#endif // LOX_EXPRESSION_H
