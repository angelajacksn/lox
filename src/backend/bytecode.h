#ifndef LOX_BYTECODE_H
#define LOX_BYTECODE_H

#include "constant_pool.h"
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
        Print, // Print the value on top of the stack
    };

    class CodeChunk
    {
    public:
        static constexpr auto kMaxConstants = std::numeric_limits<Byte>::max();

    public:
        void push_back(Byte value) { text_.push_back(value); }
        size_t size() const { return text_.size(); }
        Byte operator[](size_t index) const { return text_[index]; }
        auto& constants() { return constants_; }
        auto& constants() const { return constants_; }

    private:
        std::vector<Byte> text_;
        ConstantPool<Byte> constants_;
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
            case Print:
                return "PRINT";
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
