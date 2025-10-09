cmake_minimum_required(VERSION 3.10)
project(Set1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Ejecutable principal (con main)
add_executable(hex_to_base64
    src/hex_to_base64_main.cpp
    src/hex_to_base64.cpp
)

# Ejecutable para Fixed XOR
add_executable(fixed_xor
    src/fixed_xor_main.cpp
    src/fixed_xor.cpp
)


# Tests
enable_testing()
add_subdirectory(tests)
