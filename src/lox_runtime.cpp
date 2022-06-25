#include "lox_runtime.h"

#include <fmt/format.h>

namespace Lox
{
    LoxRuntime::LoxRuntime()
        : parser_()
    {
    }
    ReturnCode LoxRuntime::run(std::string_view source)
    {
        parser_.reset(source);
        auto result = parser_.parse();
        if (parser_.had_error())
            return ReturnCode::SyntaxError;
        return ReturnCode::Ok;
    }
    void LoxRuntime::reset()
    {
        *this = LoxRuntime();
    }
} // namespace Lox