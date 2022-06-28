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

    String::String(std::string value)
        : string_(std::move(value))
    {
    }

    String::String(std::string_view value)
        : string_(value)
    {
    }
} // namespace Lox