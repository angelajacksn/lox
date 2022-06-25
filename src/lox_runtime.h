#ifndef LOX_LOX_RUNTIME_H
#define LOX_LOX_RUNTIME_H

#include "return_codes.h"
#include "frontend/parser.h"
#include "backend/code_generator.h"
#include <string_view>

namespace Lox
{
    class LoxRuntime
    {
    public:
        LoxRuntime();
        ReturnCode run(std::string_view source);
        void reset();

    private:
        bool had_error_ = false;
        Parser parser_;
        CodeGenerator generator_;
    };

} // namespace Lox

#endif // LOX_LOX_RUNTIME_H
