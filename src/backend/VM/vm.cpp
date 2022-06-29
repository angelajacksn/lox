#include "vm.h"

#include "backend/errors/runtime_error.h"
#include "backend/errors/type_error.h"
#include <fmt/ranges.h>

namespace Lox
{
    ReturnCode VM::execute(const CodeChunk& chunk)
    {
        auto get_instruction_line = [&chunk](size_t location) {
            return chunk.get_source_location(location);
        };
        auto read_word = [&chunk](size_t& location) {
            location += 2;
            return chunk.read_word(location - 1);
        };
        auto exec_jump = [&read_word](bool condition, size_t& location) {
            auto jump_offset = read_word(location);
            if (condition)
                location += static_cast<int16_t>(jump_offset);
        };
        auto throw_unsupported_operation =
            [&get_instruction_line](const char* operator_str, size_t location, const std::vector<Object::Type>& operand_types) {
                auto message = fmt::format("unsupported operand type(s) for operator {}: {}",
                                           operator_str,
                                           fmt::join(operand_types, " and "));
                throw TypeError(get_instruction_line(location), message);
            };

        for (size_t location = 0; location < chunk.size(); ++location) {
            try {
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
                            if (!added)
                                throw_unsupported_operation("+", location, {lhs->type(), rhs->type()});
                            stack_.push(std::move(added));
                        }
                        break;
                    case Sub:
                        if (
                            auto rhs = stack_.pop();
                            auto lhs = stack_.pop()) {
                            auto subtracted = *lhs - *rhs;
                            if (!subtracted)
                                throw_unsupported_operation("-", location, {lhs->type(), rhs->type()});
                            stack_.push(subtracted);
                        }
                        break;
                    case Mul:
                        if (
                            auto rhs = stack_.pop();
                            auto lhs = stack_.pop()) {
                            auto multiplied = *lhs * *rhs;
                            if (!multiplied)
                                throw_unsupported_operation("*", location, {lhs->type(), rhs->type()});
                            stack_.push(multiplied);
                        }
                        break;
                    case Div:
                        if (
                            auto rhs = stack_.pop();
                            auto lhs = stack_.pop()) {
                            auto divided = *lhs / *rhs;
                            throw_unsupported_operation("/", location, {lhs->type(), rhs->type()});

                            stack_.push(divided);
                        }
                        break;
                    case Mod:
                        if (
                            auto rhs = stack_.pop();
                            auto lhs = stack_.pop()) {
                            auto remainder = *lhs % *rhs;
                            if (!remainder)
                                throw_unsupported_operation("%", location, {lhs->type(), rhs->type()});
                            stack_.push(remainder);
                        }
                        break;
                    case Neg:
                        if (auto operand = stack_.pop()) {
                            auto negated = -(*operand);
                            if (!negated)
                                throw_unsupported_operation("-", location, {operand->type()});
                            stack_.push(negated);
                        }
                    case Print:
                        fmt::print("{}\n", stack_.pop()->to_string());
                        break;
                    case ConstNil:
                        stack_.push(Nil::kNilRef);
                        break;
                    case ConstTrue:
                        stack_.push(Boolean::kTrueRef);
                        break;
                    case ConstFalse:
                        stack_.push(Boolean::kFalseRef);
                        break;
                    case Jump:
                        exec_jump(true, location);
                        break;
                    case JumpTrue:
                        exec_jump(*stack_.top(), location);
                        break;
                    case JumpFalse:
                        exec_jump(!(*stack_.top()), location);
                        break;
                    case JumpEq:
                        exec_jump(*stack_.pop() == *stack_.pop(), location);
                        break;
                    case JumpNe:
                        exec_jump(*stack_.pop() != *stack_.pop(), location);
                        break;
                }
            } catch (const RuntimeError& e) {
                auto& source_location = e.location();
                const auto error_code = e.error_code();
                fmt::print(stderr, "{}: {} (line: {}, column: {})\n",
                           to_string(error_code),
                           e.what(),
                           source_location.line,
                           source_location.column);
                return error_code;
            }
        }
        return ReturnCode::Ok;
    }
} // namespace Lox