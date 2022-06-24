#ifndef LOX_SYNTAX_ERROR_H
#define LOX_SYNTAX_ERROR_H

#include "token.h"
#include <fmt/format.h>
#include <stdexcept>

namespace Lox
{
    class SyntaxError : public std::runtime_error
    {
    public:
        SyntaxError(const char* message, size_t line, size_t column)
            : std::runtime_error(fmt::format("{} (line: {}, column: {})", message, line, column))
            , line_(line)
            , column_(column)
        {
        }

        size_t line() const { return line_; }
        size_t column() const { return column_; }

    private:
        size_t line_;
        size_t column_;
    };

} // namespace Lox

#endif // LOX_SYNTAX_ERROR_H
