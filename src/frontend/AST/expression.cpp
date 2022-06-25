#include "expression.h"

namespace Lox
{
    BinaryExpr::BinaryExpr(Expression::Ptr left, Token binary_operator, Expression::Ptr right)
        : left_(std::move(left))
        , operator_(std::move(binary_operator))
        , right_(std::move(right))
    {
    }

    UnaryExpr::UnaryExpr(Expression::Ptr operand, Token unary_operator)
        : operand_(std::move(operand))
        , operator_(std::move(unary_operator))
    {
    }

    LiteralExpr::LiteralExpr(Object::Ptr value)
        : value_(std::move(value))
    {
    }

    GroupingExpr::GroupingExpr(Expression::Ptr expression)
        : expression_(std::move(expression))
    {
    }
} // namespace Lox
