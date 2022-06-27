#include "statement.h"

namespace Lox
{
    PrintStmt::PrintStmt(Expression::Ptr expression)
        : expression_(std::move(expression))
    {
    }

    ExpressionStmt::ExpressionStmt(Expression::Ptr expression)
        : expression_(std::move(expression))
    {
    }
} // namespace Lox