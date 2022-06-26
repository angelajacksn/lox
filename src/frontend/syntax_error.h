#ifndef LOX_SYNTAX_ERROR_H
#define LOX_SYNTAX_ERROR_H

#include "common/source_location.h"
#include "token.h"
#include <fmt/format.h>
#include <stdexcept>

namespace Lox
{
    class SyntaxError : public std::runtime_error
    {
    public:
        SyntaxError(auto message, SourceLocation location)
            : std::runtime_error(fmt::format("{} (line: {}, column: {})", message, location.line, location.column))
            , location_(std::move(location))
        {
        }

        const SourceLocation& location() const { return location_; }

    private:
        SourceLocation location_;
    };

} // namespace Lox

#endif // LOX_SYNTAX_ERROR_H
