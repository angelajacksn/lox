#ifndef LOX_VM_ERROR_H
#define LOX_VM_ERROR_H

#include <stdexcept>

namespace Lox
{
    class VMError : public std::runtime_error
    {
    public:
        VMError()
            : std::runtime_error("An internal Lox VM error occurred")
        {
        }
        VMError(const std::string& msg)
            : std::runtime_error(msg)
        {
        }
    };

} // namespace Lox

#endif // LOX_VM_ERROR_H
