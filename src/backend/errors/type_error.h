#ifndef LOX_TYPE_ERROR_H
#define LOX_TYPE_ERROR_H

#include "runtime_error.h"

namespace Lox
{
    class TypeError : public RuntimeError
    {
    public:
        TypeError(SourceLocation location, const std::string& message = "A type error occurred")
            : RuntimeError(location, message)
        {
        }

        ReturnCode error_code() const override { return ReturnCode::TypeError; }
    };

} // namespace Lox

#endif // LOX_TYPE_ERROR_H
