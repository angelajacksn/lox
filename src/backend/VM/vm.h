#ifndef LOX_VM_H
#define LOX_VM_H

#include "backend/bytecode.h"
#include "backend/stack.h"
#include "return_codes.h"

namespace Lox
{
    class VM
    {
    public:
        ReturnCode execute(const CodeChunk& chunk);
        const Stack& stack() const { return stack_; }

    private:
        Stack stack_;
    };

} // namespace Lox

#endif // LOX_VM_H
