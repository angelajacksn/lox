cmake_minimum_required(VERSION 3.12)

set (LOX_VERSION_MAJOR 0)
set (LOX_VERSION_MINOR 1)
set (LOX_VERSION_PATCH 0)

project (lox
        VERSION "${LOX_VERSION_MAJOR}.${LOX_VERSION_MINOR}.${LOX_VERSION_PATCH}"
        DESCRIPTION "Lox interpreter written in C++ 20"
        LANGUAGES C CXX
        )

add_subdirectory(external/fmt)

add_executable(lox src/main.cpp)
target_link_libraries(lox PRIVATE fmt::fmt)
target_compile_features(lox PRIVATE cxx_std_20)
