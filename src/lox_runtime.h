#ifndef LOX_LOX_RUNTIME_H
#define LOX_LOX_RUNTIME_H

#include "return_codes.h"
#include <string_view>

namespace Lox
{
    class LoxRuntime
    {
    public:
        ReturnCode run(std::string_view source);
        void reset();

    private:
        bool had_error_ = false;
    };

} // namespace Lox

#endif // LOX_LOX_RUNTIME_H
