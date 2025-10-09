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

# Ejecutable para Single-byte XOR cipher
add_executable(single_byte_xor
    src/single_byte_xor_main.cpp
    src/single_byte_xor.cpp
)

# Ejecutable para Detect Single-Byte XOR
add_executable(detect_single_byte_xor
    src/detect_single_byte_xor_main.cpp
    src/detect_single_byte_xor.cpp
    src/single_byte_xor.cpp
)

add_executable(repeating_key_xor
    src/repeating_key_xor.cpp
    src/repeating_key_xor_main.cpp
)

find_package(OpenSSL REQUIRED)

add_executable(break_repeating_key_xor
    src/break_repeating_key_xor.cpp
    src/hamming_distance.cpp
    src/break_repeating_key_xor_main.cpp
    src/single_byte_xor.cpp
)

target_include_directories(break_repeating_key_xor PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(break_repeating_key_xor PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Ejecutable para AES-ECB
add_executable(aes_ecb_decrypt
    src/aes_ecb.cpp
    src/aes_ecb_main.cpp
)

target_include_directories(aes_ecb_decrypt PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(aes_ecb_decrypt PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Ejecutable para Detect ECB
add_executable(detect_ecb
    src/detect_ecb_main.cpp
)

target_include_directories(detect_ecb PRIVATE ${CMAKE_SOURCE_DIR}/include)


# Tests
enable_testing()
add_subdirectory(tests)
