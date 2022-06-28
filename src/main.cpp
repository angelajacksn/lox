#include "return_codes.h"
#include "lox_runtime.h"
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <string>

Lox::ReturnCode run(std::istream& istream) {
    Lox::LoxRuntime runtime;
    std::string input;
    auto last_operation = Lox::ReturnCode::Ok;
    while (true) {
        fmt::print(">>> ");
        if (!std::getline(istream, input) || input == "exit")
            break;
        last_operation = runtime.run(input);
    }
    return last_operation;
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
    Lox::LoxRuntime runtime;
    return runtime.run(source);
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
        return static_cast<int>(result);
    }
    return static_cast<int>(Lox::ReturnCode::Ok);
}