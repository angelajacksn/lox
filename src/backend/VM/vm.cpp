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
                        auto rhs = std::dynamic_pointer_cast<Number>(stack_.pop());
                        auto lhs = std::dynamic_pointer_cast<Number>(stack_.pop())) {
                        auto added = run_binary_op(*lhs, *rhs, std::plus<>());
                        stack_.push(Object::create<Number>(added));
                    }
                    break;
                case Sub:
                    if (
                        auto rhs = std::dynamic_pointer_cast<Number>(stack_.pop());
                        auto lhs = std::dynamic_pointer_cast<Number>(stack_.pop())) {
                        auto subtracted = run_binary_op(*lhs, *rhs, std::minus<>());
                        stack_.push(Object::create<Number>(subtracted));
                    }
                    break;
                case Mul:
                    if (
                        auto rhs = std::dynamic_pointer_cast<Number>(stack_.pop());
                        auto lhs = std::dynamic_pointer_cast<Number>(stack_.pop())) {
                        auto multiplied = run_binary_op(*lhs, *rhs, std::multiplies<>());
                        stack_.push(Object::create<Number>(multiplied));
                    }
                    break;
                case Div:
                    if (
                        auto rhs = std::dynamic_pointer_cast<Number>(stack_.pop());
                        auto lhs = std::dynamic_pointer_cast<Number>(stack_.pop())) {
                        auto divided = run_binary_op(*lhs, *rhs, std::divides<>());
                        stack_.push(Object::create<Number>(divided));
                    }
                    break;
                case Mod:
                    if (
                        auto rhs = std::dynamic_pointer_cast<Number>(stack_.pop());
                        auto lhs = std::dynamic_pointer_cast<Number>(stack_.pop())) {
                        auto remainder = run_binary_op(*lhs, *rhs, std::modulus<>());
                        stack_.push(Object::create<Number>(remainder));
                    }
                    break;
                case Neg:
                    if (auto operand = std::dynamic_pointer_cast<Number>(stack_.pop())) {
                        auto negated = -(*operand);
                        stack_.push(Object::create<Number>(negated));
                    }
                case Print:
                    fmt::print("{}\n", stack_.pop()->to_string());
                    break;
            }
        }
        return ReturnCode::Ok;
    }
} // namespace Lox