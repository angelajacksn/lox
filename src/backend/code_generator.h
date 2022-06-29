#ifndef LOX_CODE_GENERATOR_H
#define LOX_CODE_GENERATOR_H

#include "bytecode.h"
#include "frontend/AST/expression.h"
#include "frontend/AST/statement.h"
#include <vector>

namespace Lox
{
    class CodeGenerator : public ExpressionVisitor, public StatementVisitor
    {
    public:
        CodeChunk generate(const std::vector<Statement::Ptr>& program);

        Object::Ptr visit(const BinaryExpr& expr) override;
        Object::Ptr visit(const UnaryExpr& expr) override;
        Object::Ptr visit(const LiteralExpr& expr) override;
        Object::Ptr visit(const GroupingExpr& expr) override;
        Object::Ptr visit(const LogicalExpr& expr) override;

        void visit(const PrintStmt& stmt) override;
        void visit(const ExpressionStmt& stmt) override;

    private:
        void generate_code(const Expression& expression) { expression.accept(*this); }
        void generate_code(const Statement& statement) { statement.accept(*this); }

        template<typename... Args>
        void write_instruction(SourceLocation location, Instruction instruction, Args&&... args)
        {
            code_.push_back(static_cast<Byte>(instruction), location);
            (code_.push_back(static_cast<Byte>(args), location), ...);
        }

        void add_constant(SourceLocation location, Object::Ptr value)
        {
            auto constant_index = code_.constants().push(std::move(value));
            write_instruction(location, Instruction::PushC, constant_index);
        }

        void patch(size_t index, Byte value)
        {
            code_[index] = value;
        }

    private:
        CodeChunk code_;
    };

} // namespace Lox

#endif // LOX_CODE_GENERATOR_H
