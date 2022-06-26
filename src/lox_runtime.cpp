#include "lox_runtime.h"

#include "backend/code_generator.h"
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

        auto byte_code = CodeGenerator().generate(ast);
        if constexpr (kPrintDisassembly)
            Disassembler().disassemble(byte_code);

        auto exec_result = vm_.execute(byte_code);
        fmt::print("{}\n", vm_.stack().top()->to_string());

        return exec_result;
    }
    void LoxRuntime::reset()
    {
        *this = LoxRuntime();
    }
} // namespace Lox