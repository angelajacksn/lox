#include "vm.h"

namespace Lox
{
    ReturnCode VM::execute(const CodeChunk& chunk)
    {
        auto run_binary_op = [](auto lhs, auto rhs, auto binary_op) {
            return binary_op(lhs, rhs);
        };

        for (size_t location = 0; location < chunk.size(); ++location) {
            auto instruction = static_cast<Instruction>(chunk[location]);
            using enum Instruction;
            switch (instruction) {
                case Nop:
                    break;
                case Push:
                    stack_.push(Object::create<Number>(chunk[++location]));
                    break;
                case PushC:
                    stack_.push(chunk.constants().get(chunk[++location]));
                    break;
                case Pop:
                    stack_.pop();
                    break;
                case Add:
                    if (
                        auto rhs = stack_.pop();
                        auto lhs = stack_.pop()) {
                        auto added = *rhs + *lhs;
                        stack_.push(std::move(added));
                    }
                    break;
                case Sub:
                    if (
                        auto rhs = stack_.pop();
                        auto lhs = stack_.pop()) {
                        auto subtracted = *lhs - *rhs;
                        stack_.push(subtracted);
                    }
                    break;
                case Mul:
                    if (
                        auto rhs = stack_.pop();
                        auto lhs = stack_.pop()) {
                        auto multiplied = *lhs * *rhs;
                        stack_.push(multiplied);
                    }
                    break;
                case Div:
                    if (
                        auto rhs = stack_.pop();
                        auto lhs = stack_.pop()) {
                        auto divided = *lhs / *rhs;
                        stack_.push(divided);
                    }
                    break;
                case Mod:
                    if (
                        auto rhs = stack_.pop();
                        auto lhs = stack_.pop()) {
                        auto remainder = *lhs % *rhs;
                        stack_.push(remainder);
                    }
                    break;
                case Neg:
                    if (auto operand = stack_.pop()) {
                        auto negated = -(*operand);
                        stack_.push(negated);
                    }
                case Print:
                    fmt::print("{}\n", stack_.pop()->to_string());
                    break;
            }
        }
        return ReturnCode::Ok;
    }
} // namespace Lox