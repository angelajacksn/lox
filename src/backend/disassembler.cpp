#include "disassembler.h"

#include <fmt/format.h>

namespace Lox
{
    void Disassembler::disassemble(const CodeChunk& chunk)
    {
        for (size_t location = 0; location < chunk.size(); ++location) {
            fmt::print("{:#X} ", location);
            auto instruction = static_cast<Instruction>(chunk[location]);
            switch (instruction) {
                case Instruction::Push:
                    fmt::print("{} {}\n", instruction, ++location);
                    break;
                case Instruction::PushC: {
                    auto constant_index = chunk[++location];
                    fmt::print("{} {} ({})\n", instruction, constant_index, chunk.get_constant(constant_index)->to_string());
                    break;
                }
                default:
                    fmt::print("{}\n", instruction);
            }
        }
    }
} // namespace Lox