#include "lox_runtime.h"

#include "backend/disassembler.h"
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

        auto ast = parser_.parse();
        if (parser_.had_error())
            return ReturnCode::SyntaxError;

        auto byte_code = generator_.generate(ast);
        Disassembler disassembler;
        disassembler.disassemble(byte_code);

        return ReturnCode::Ok;
    }
    void LoxRuntime::reset()
    {
        *this = LoxRuntime();
    }
} // namespace Lox