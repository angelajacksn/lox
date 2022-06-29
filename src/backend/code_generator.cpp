#include "code_generator.h"

namespace Lox
{
    CodeChunk CodeGenerator::generate(const std::vector<Statement::Ptr>& program)
    {
        for (auto& statement : program)
            generate_code(*statement);
        return code_;
    }

    Object::Ptr CodeGenerator::visit(const BinaryExpr& expr)
    {
        generate_code(expr.left());
        generate_code(expr.right());
        switch (expr.binary_operator().type) {
            case Token::Type::Plus:
                write_instruction(expr.source_location(), Instruction::Add);
                break;
            case Token::Type::Minus:
                write_instruction(expr.source_location(), Instruction::Sub);
                break;
            case Token::Type::Star:
                write_instruction(expr.source_location(), Instruction::Mul);
                break;
            case Token::Type::Slash:
                write_instruction(expr.source_location(), Instruction::Div);
                break;
            case Token::Type::Modulus:
                write_instruction(expr.source_location(), Instruction::Mod);
                break;
            case Token::Type::EqualEqual:
                write_instruction(expr.source_location(), Instruction::JumpNe, 0x00, 0x04);
                write_instruction(expr.source_location(), Instruction::ConstTrue);
                write_instruction(expr.source_location(), Instruction::Jump, 0x00, 0x01);
                write_instruction(expr.source_location(), Instruction::ConstFalse);
                break;
            case Token::Type::BangEqual:
                write_instruction(expr.source_location(), Instruction::JumpEq, 0x00, 0x04);
                write_instruction(expr.source_location(), Instruction::ConstTrue);
                write_instruction(expr.source_location(), Instruction::Jump, 0x00, 0x01);
                write_instruction(expr.source_location(), Instruction::ConstFalse);
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
                write_instruction(expr.source_location(), Instruction::Neg);
                break;
            default:
                break;
        }
        return nullptr;
    }

    Object::Ptr CodeGenerator::visit(const LiteralExpr& expr)
    {
        auto& obj = expr.value();
        if (auto const_boolean = dynamic_cast<const Boolean*>(&obj))
            write_instruction(expr.source_location(),
                              *const_boolean ? Instruction::ConstTrue : Instruction::ConstFalse);
        else
            add_constant(expr.source_location(), expr.share_object());

        return nullptr;
    }

    Object::Ptr CodeGenerator::visit(const GroupingExpr& expr)
    {
        generate_code(expr.expression());
        return nullptr;
    }

    Object::Ptr CodeGenerator::visit(const LogicalExpr& expr)
    {
        auto location = expr.source_location();
        auto jump_type = expr.logical_operator().type == Token::Type::And ? Instruction::JumpFalse : Instruction::JumpTrue;

        generate_code(expr.left());
        auto jump_offset_location = code_.size() + 1;
        write_instruction(location, jump_type, Instruction::Nop, Instruction::Nop);

        auto block_begin = code_.size();
        write_instruction(location, Instruction::Pop);
        generate_code(expr.right());
        auto jump_offset = code_.size() - block_begin;

        Byte jump_offset_hi_byte = jump_offset << 8;
        Byte jump_offset_lo_byte = jump_offset;
        patch(jump_offset_location++, jump_offset_hi_byte);
        patch(jump_offset_location, jump_offset_lo_byte);
        return nullptr;
    }

    void CodeGenerator::visit(const PrintStmt& stmt)
    {
        generate_code(stmt.expression());
        write_instruction(stmt.expression().source_location(), Instruction::Print);
    }

    void CodeGenerator::visit(const ExpressionStmt& stmt)
    {
        generate_code(stmt.expression());
    }
} // namespace Lox