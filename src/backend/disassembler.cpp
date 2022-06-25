#include "disassembler.h"

#include <fmt/format.h>

namespace Lox
{
    void Disassembler::disassemble(const CodeChunk& chunk)
    {
        for (size_t location = 0; location < chunk.size(); ++location) {
            auto read_number = [&]{
                auto value = read_double(chunk, ++location);
                location += sizeof(double) - 1;
                return value;
            };

            fmt::print("{:#X} ", location);
            auto instruction = static_cast<Instruction>(chunk[location]);
            switch (instruction) {
                case Instruction::Push:
                    fmt::print("{} {}\n", instruction, read_number());
                    break;
                default:
                    fmt::print("{}\n", instruction);
            }
        }
    }
} // namespace Lox