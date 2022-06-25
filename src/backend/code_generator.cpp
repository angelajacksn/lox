#include "code_generator.h"

namespace Lox
{
    CodeChunk CodeGenerator::generate(const Expression::Ptr& expression)
    {
        generate_code(*expression);
        return code_;
    }

    Object::Ptr CodeGenerator::visit(const BinaryExpr& expr)
    {
        generate_code(expr.left());
        generate_code(expr.right());
        switch (expr.binary_operator().type) {
            case Token::Type::Plus:
                write_instruction(Instruction::Add);
                break;
            case Token::Type::Minus:
                write_instruction(Instruction::Sub);
                break;
            case Token::Type::Star:
                write_instruction(Instruction::Mul);
                break;
            case Token::Type::Slash:
                write_instruction(Instruction::Div);
                break;
            default:
                break;
        }
        return nullptr;
    }

    Object::Ptr CodeGenerator::visit(const UnaryExpr& expr)
    {
        generate_code(expr.operand());
        switch (expr.unary_operator().type) {
            case Token::Type::Minus:
                write_instruction(Instruction::Neg);
                break;
            default:
                break;
        }
        return nullptr;
    }

    Object::Ptr CodeGenerator::visit(const LiteralExpr& expr)
    {
        add_constant(expr.share_object());
        return nullptr;
    }

    Object::Ptr CodeGenerator::visit(const GroupingExpr& expr)
    {
        generate_code(expr.expression());
        return nullptr;
    }
} // namespace Lox