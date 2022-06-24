#include "return_codes.h"
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <string>

Lox::ReturnCode run(std::istream& istream) {
    std::string input;
    while (input != "exit") {
        fmt::print(">>> ");
        if (!std::getline(istream, input))
            break;
        fmt::print("{}\n", input);
    }
    return Lox::ReturnCode::Ok;
}

Lox::ReturnCode run(std::ifstream& file) {
    file.seekg(0, std::ios::end);
    const auto size = file.tellg();
    file.seekg(0);
    std::string source(size, ' ');
    if (!file.read(source.data(), size)) {
        fmt::print(stderr, "Failed to read from source file\n");
        return Lox::ReturnCode::IOError;
    }
    fmt::print("{}\n", source);
    return Lox::ReturnCode::Ok;
}

int main(int argc, const char* argv[])
{
    if (argc == 1)
        run(std::cin);
    else {
        const auto filename = argv[1];
        std::ifstream source_file(filename);
        if (source_file.fail()) {
            fmt::print(stderr, "Failed to open file '{}': {} [errno: {}]", filename, strerror(errno), errno);
            return static_cast<int>(Lox::ReturnCode::IOError);
        }
        const auto result = run(source_file);
        if (result != Lox::ReturnCode::Ok) {
            fmt::print(stderr, "{}", Lox::get_return_code_msg(result));
            return static_cast<int>(result);
        }
        return static_cast<int>(Lox::ReturnCode::Ok);
    }
    return static_cast<int>(Lox::ReturnCode::Ok);
}