#ifndef LOX_RETURN_CODES_H
#define LOX_RETURN_CODES_H

namespace Lox {
    enum class ReturnCode {
        Ok = 0,
        IOError,
        SyntaxError,
        RuntimeError
    };

    constexpr const char* get_return_code_msg(ReturnCode code) {
        using enum ReturnCode;
        switch (code) {
            case Ok:
                return "No error";
            case IOError:
                return "An IO error occurred";
            case SyntaxError:
                return "Syntax error in source";
            case RuntimeError:
                return "A runtime error occurred";
        }
        return "Invalid return code";
    }
}

#endif // LOX_RETURN_CODES_H
