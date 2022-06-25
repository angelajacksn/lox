#ifndef LOX_BYTECODE_H
#define LOX_BYTECODE_H

#include <cstdint>
#include <vector>
#include <fmt/format.h>

namespace Lox {
    enum class Instruction : uint8_t {
        Nop = 0x0,  // No operation
        Push,       // Push value onto the stack
        Pop,        // Pop value from the stack
        Add,        // Add the 2 values on top of the stack
        Sub,        // Subtract the 2 values on top of the stack
        Mul,        // Multiply the 2 values on top of the stack
        Div,        // Divide the 2 values on top of the stack
    };

    using InstructionChunk = std::vector<Instruction>;

    constexpr const char* to_string(Instruction instruction) {
        using enum Instruction;
        switch (instruction) {
            case Nop:
                return "NOP";
            case Push:
                return "PUSH";
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
        }
        return "???";
    }
}

template<>
struct fmt::formatter<Lox::Instruction> {
    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(Lox::Instruction instruction, FormatContext& ctx) const -> decltype(ctx.out())
    {
        return format_to(ctx.out(), "{}",Lox::to_string(instruction));
    }
};

#endif // LOX_BYTECODE_H
