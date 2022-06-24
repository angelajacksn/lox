#include "lox_runtime.h"
#include <fmt/format.h>

namespace Lox
{
    ReturnCode LoxRuntime::run(std::string_view source)
    {
        fmt::print("{}\n", source);
        return ReturnCode::Ok;
    }
    void LoxRuntime::reset()
    {
        *this = LoxRuntime();
    }
} // namespace Lox