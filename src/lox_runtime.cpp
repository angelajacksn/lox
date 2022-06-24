#include "lox_runtime.h"

#include <fmt/format.h>

namespace Lox
{
    ReturnCode LoxRuntime::run(std::string_view source)
    {
        scanner_.reset(source);
        for (auto token = scanner_.next_token(); token.type != Token::Type::Eof; token = scanner_.next_token())
            fmt::print("{}\n", token);
        return ReturnCode::Ok;
    }
    void LoxRuntime::reset()
    {
        *this = LoxRuntime();
    }
} // namespace Lox