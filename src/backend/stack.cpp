//
// Created by sarpsenturk on 26.06.2022.
//

#include "stack.h"

namespace Lox
{
    void Stack::push(Byte byte)
    {
        stack_.push(byte);
    }

    Byte Stack::pop()
    {
        auto value = stack_.top();
        stack_.pop();
        return value;
    }

    Byte Stack::top() const
    {
        return stack_.top();
    }

    bool Stack::empty() const
    {
        return stack_.empty();
    }
} // namespace Lox