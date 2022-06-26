#ifndef LOX_OUT_OF_MEMORY_ERROR_H
#define LOX_OUT_OF_MEMORY_ERROR_H

#include "vm_error.h"

namespace Lox
{
    class OutOfMemoryError : public VMError
    {
    public:
        OutOfMemoryError() : VMError("The lox VM has ran out of memory") {}
    };

} // namespace Lox

#endif // LOX_OUT_OF_MEMORY_ERROR_H
