#ifndef LOX_RETURN_CODES_H
#define LOX_RETURN_CODES_H

namespace Lox {
    enum class ReturnCode {
        Ok = 0,
        IOError
    };

    constexpr const char* get_return_code_msg(ReturnCode code) {
        using enum ReturnCode;
        switch (code) {
            case Ok:
                return "No error";
            case IOError:
                return "An IO error occurred";
        }
    }
}

#endif // LOX_RETURN_CODES_H
