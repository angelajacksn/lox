#ifndef LOX_LOX_RUNTIME_H
#define LOX_LOX_RUNTIME_H

#include "backend/VM/vm.h"
#include "frontend/parser.h"
#include "return_codes.h"
#include <string_view>

namespace Lox
{
    class LoxRuntime
    {
    public:
        static constexpr bool kPrintDisassembly = true;
        
        LoxRuntime();
        ReturnCode run(std::string_view source);
        void reset();

    private:
        bool had_error_ = false;
        Parser parser_;
        VM vm_;
    };

} // namespace Lox

#endif // LOX_LOX_RUNTIME_H
