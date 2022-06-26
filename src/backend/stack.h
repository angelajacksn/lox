#ifndef LOX_STACK_H
#define LOX_STACK_H

#include "bytecode.h"
#include "common/object.h"
#include <stack>

namespace Lox
{
    class Stack
    {
    public:
        void push(Object::Ptr object);
        Object::Ptr pop();
        Object* top() const;
        bool empty() const;

    private:
        std::stack<Object::Ptr> stack_;
    };
} // namespace Lox

#endif // LOX_STACK_H
