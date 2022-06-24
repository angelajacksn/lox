#include "object.h"

namespace Lox
{
    Number::Number(double value)
        : value_(value)
        , string_(std::to_string(value))
    {
    }

    Number::Number(std::string_view value)
        : value_(std::stod(value.data()))
        , string_(value)
    {
    }

    Object::Type Number::type() const
    {
        return Type::Nil;
    }
} // namespace Lox