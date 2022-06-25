#ifndef LOX_DISASSEMBLER_H
#define LOX_DISASSEMBLER_H

#include "bytecode.h"

namespace Lox
{
    class Disassembler
    {
    public:
        void disassemble(const CodeChunk& chunk);
    };
} // namespace Lox

#endif // LOX_DISASSEMBLER_H
