#ifndef LOX_RUNTIME_ERROR_H
#define LOX_RUNTIME_ERROR_H

#include "common/source_location.h"
#include "return_codes.h"
#include <fmt/format.h>
#include <stdexcept>

namespace Lox
{
    class RuntimeError : public std::runtime_error
    {
    public:
        RuntimeError(SourceLocation location, const std::string& message = "A runtime error occurred")
            : std::runtime_error(message)
            , location_(std::move(location))
        {
        }

        const SourceLocation& location() const { return location_; }
        virtual ReturnCode error_code() const { return ReturnCode::RuntimeError; }

    private:
        SourceLocation location_;
    };

} // namespace Lox

#endif // LOX_RUNTIME_ERROR_H
