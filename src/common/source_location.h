#ifndef LOX_SOURCE_LOCATION_H
#define LOX_SOURCE_LOCATION_H

#include <cstddef>

namespace Lox
{
    struct SourceLocation
    {
        size_t line = 1;
        size_t column = 0;

        void advance() {++column;}
        void new_line() {++line; column = 0;}
    };

} // namespace Lox

#endif // LOX_SOURCE_LOCATION_H
