cmake_minimum_required(VERSION 3.12)

set(LOX_VERSION_MAJOR 0)
set(LOX_VERSION_MINOR 1)
set(LOX_VERSION_PATCH 0)

project(lox
        VERSION "${LOX_VERSION_MAJOR}.${LOX_VERSION_MINOR}.${LOX_VERSION_PATCH}"
        DESCRIPTION "Lox interpreter written in C++ 20"
        LANGUAGES C CXX
        )

add_subdirectory(external/fmt)

add_executable(lox
        src/main.cpp
        src/return_codes.h
        src/lox_runtime.cpp
        src/lox_runtime.h
        src/frontend/token.h
        src/frontend/scanner.cpp
        src/frontend/scanner.h
        src/frontend/syntax_error.h
        src/frontend/parser.cpp
        src/frontend/parser.h
        src/common/object.cpp
        src/common/object.h
        src/common/source_location.h
        src/frontend/AST/expression.h
        src/frontend/AST/expression.cpp
        src/backend/bytecode.h
        src/backend/stack.h
        src/backend/stack.cpp
        src/backend/code_generator.h
        src/backend/code_generator.cpp
        src/backend/disassembler.h
        src/backend/disassembler.cpp
        src/backend/errors/vm_error.h
        src/backend/errors/out_of_memory_error.h
        src/backend/constant_pool.h
        src/backend/VM/vm.h
        src/backend/VM/vm.cpp)
target_link_libraries(lox PRIVATE fmt::fmt)
target_include_directories(lox PRIVATE ./src)
target_compile_features(lox PRIVATE cxx_std_20)
