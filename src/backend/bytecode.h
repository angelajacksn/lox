#ifndef LOX_BYTECODE_H
#define LOX_BYTECODE_H

#include "common/source_location.h"
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
        Mod, // Perform modulus on the 2 values on top of the stack
        Neg, // Negate the value on top of the stack
        Print, // Print the value on top of the stack
        ConstNil, // Push a nil reference onto the stack
        ConstTrue, // Push boolean true onto the stack
        ConstFalse, // Push boolean false onto the stack
    };

    class CodeChunk
    {
    public:
        static constexpr auto kMaxConstants = std::numeric_limits<Byte>::max();

    public:
        void push_back(Byte value, SourceLocation location)
        {
            text_.push_back(value);
            line_information_.push_back(std::move(location));
        }
        size_t size() const { return text_.size(); }
        Byte operator[](size_t index) const { return text_[index]; }
        const SourceLocation& get_source_location(size_t instruction_index) const { return line_information_[instruction_index]; }
        auto& constants() { return constants_; }
        auto& constants() const { return constants_; }

    private:
        std::vector<Byte> text_;
        std::vector<SourceLocation> line_information_;
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
            case Mod:
                return "MOD";
            case Neg:
                return "NEG";
            case Print:
                return "PRINT";
            case ConstNil:
                return "CONST_NIL";
            case ConstTrue:
                return "CONST_TRUE";
            case ConstFalse:
                return "CONST_FALSE";
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
