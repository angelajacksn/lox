#include "disassembler.h"

#include <fmt/format.h>

namespace Lox
{
    void Disassembler::disassemble(const CodeChunk& chunk)
    {
        fmt::print("{:=^20}\n", "Disassembly");
        for (size_t location = 0; location < chunk.size(); ++location) {
            fmt::print("{:#X} ", location);
            auto instruction = static_cast<Instruction>(chunk[location]);
            switch (instruction) {
                case Instruction::Push:
                    fmt::print("{} {}\n", instruction, ++location);
                    break;
                case Instruction::PushC: {
                    auto constant_index = chunk[++location];
                    fmt::print("{} {} ({})\n", instruction, constant_index, chunk.constants().get(constant_index)->to_string());
                    break;
                }
                default:
                    fmt::print("{}\n", instruction);
            }
        }
        fmt::print("{:=^20}\n", "Disassembly");
    }
} // namespace Lox