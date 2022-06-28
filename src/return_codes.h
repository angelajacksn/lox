#ifndef LOX_RETURN_CODES_H
#define LOX_RETURN_CODES_H

namespace Lox {
    enum class ReturnCode {
        Ok = 0,
        IOError,
        SyntaxError,
        RuntimeError,
        TypeError
    };

    constexpr const char* to_string(ReturnCode code) {
        using enum ReturnCode;
        switch (code) {
            case Ok:
                return "OK";
            case IOError:
                return "IOError";
            case SyntaxError:
                return "SyntaxError";
            case RuntimeError:
                return "RuntimeError";
            case TypeError:
                return "TypeError";
        }
        return "Invalid return code";
    }
}

#endif // LOX_RETURN_CODES_H
