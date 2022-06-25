#ifndef LOX_BYTECODE_H
#define LOX_BYTECODE_H

#include "common/object.h"
#include <array>
#include <cstdint>
#include <fmt/format.h>
#include <vector>

namespace Lox
{
    using Byte = uint8_t;

    enum class Instruction : Byte {
        Nop = 0x0, // No operation
        Push, // Push value onto the stack
        PushC, // Push constant with index onto the stack
        Pop, // Pop value from the stack
        Add, // Add the 2 values on top of the stack
        Sub, // Subtract the 2 values on top of the stack
        Mul, // Multiply the 2 values on top of the stack
        Div, // Divide the 2 values on top of the stack
        Neg, // Negate the value on top of the stack
    };

    class CodeChunk
    {
    public:
        static constexpr auto kMaxConstants = std::numeric_limits<Byte>::max();

    public:
        CodeChunk() { constants_.fill(nullptr); }

        void push_back(Byte value) { text_.push_back(value); }
        size_t size() const { return text_.size(); }
        Byte operator[](size_t index) const { return text_[index]; }

        Byte push_constant(Object::Ptr value)
        {
            if (last_constant_index_ >= kMaxConstants - 1) {
                // TODO: Throw exception / do assertion
                return -1;
            }
            auto index = last_constant_index_++;
            constants_[index] = std::move(value);
            return index;
        }

        Object::Ptr get_constant(size_t index) const
        {
            if (index >= kMaxConstants) {
                // TODO: Throw exception / do assertion
                return nullptr;
            }
            return constants_[index];
        }

    private:
        std::vector<Byte> text_;

        std::array<Object::Ptr, kMaxConstants> constants_;
        Byte last_constant_index_ = 0;
    };

    constexpr const char* to_string(Instruction instruction)
    {
        using enum Instruction;
        switch (instruction) {
            case Nop:
                return "NOP";
            case Push:
                return "PUSH";
            case PushC:
                return "PUSH_C";
            case Pop:
                return "POP";
            case Add:
                return "ADD";
            case Sub:
                return "SUB";
            case Mul:
                return "MUL";
            case Div:
                return "DIV";
            case Neg:
                return "NEG";
        }
        return "???";
    }
} // namespace Lox

template<>
struct fmt::formatter<Lox::Instruction> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(Lox::Instruction instruction, FormatContext& ctx) const -> decltype(ctx.out())
    {
        return format_to(ctx.out(), "{}", Lox::to_string(instruction));
    }
};

#endif // LOX_BYTECODE_H
