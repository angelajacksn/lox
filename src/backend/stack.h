#ifndef LOX_STACK_H
#define LOX_STACK_H

#include "bytecode.h"
#include <stack>

namespace Lox
{
    class Stack
    {
    public:
        void push(Byte byte);
        Byte pop();
        Byte top() const;
        bool empty() const;

    private:
        std::stack<Byte> stack_;
    };
} // namespace Lox

#endif // LOX_STACK_H
