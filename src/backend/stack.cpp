#include "stack.h"

namespace Lox
{
    void Stack::push(Object::Ptr object)
    {
        stack_.push(std::move(object));
    }

    Object::Ptr Stack::pop()
    {
        auto value = stack_.top();
        stack_.pop();
        return value;
    }

    Object* Stack::top() const
    {
        return stack_.top().get();
    }

    bool Stack::empty() const
    {
        return stack_.empty();
    }
} // namespace Lox