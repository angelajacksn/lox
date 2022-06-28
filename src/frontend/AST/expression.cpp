#include "expression.h"

namespace Lox
{
    BinaryExpr::BinaryExpr(Expression::Ptr left, Token binary_operator, Expression::Ptr right)
        : left_(std::move(left))
        , operator_(binary_operator)
        , right_(std::move(right))
    {
    }

    UnaryExpr::UnaryExpr(Expression::Ptr operand, Token unary_operator)
        : operand_(std::move(operand))
        , operator_(unary_operator)
    {
    }

    LiteralExpr::LiteralExpr(Object::Ptr value, SourceLocation location)
        : value_(std::move(value))
        , source_location_(location)
    {
    }

    GroupingExpr::GroupingExpr(Expression::Ptr expression)
        : expression_(std::move(expression))
    {
    }

    LogicalExpr::LogicalExpr(Expression::Ptr left, Token logical_operator, Expression::Ptr right)
        : left_(std::move(left))
        , operator_(logical_operator)
        , right_(std::move(right))
    {
    }
} // namespace Lox
