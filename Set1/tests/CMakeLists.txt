cmake_minimum_required(VERSION 3.10)

# Encuentra GTest y OpenSSL
find_package(GTest REQUIRED)
find_package(OpenSSL REQUIRED)

# Ejecutable de tests
add_executable(run_tests
    test_hex_to_base64.cpp
    ${CMAKE_SOURCE_DIR}/src/hex_to_base64.cpp
)

target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_tests PRIVATE GTest::gtest_main)

add_test(NAME hex_to_base64_tests COMMAND run_tests)

# Ejecutable de tests para Fixed XOR
add_executable(run_fixed_xor_tests
    test_fixed_xor.cpp
    ${CMAKE_SOURCE_DIR}/src/fixed_xor.cpp
)

target_include_directories(run_fixed_xor_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_fixed_xor_tests PRIVATE GTest::gtest_main)

add_test(NAME fixed_xor_tests COMMAND run_fixed_xor_tests)

# Ejecutable de tests para Single-byte XOR cipher
add_executable(run_single_byte_xor_tests
    test_single_byte_xor.cpp
    ${CMAKE_SOURCE_DIR}/src/single_byte_xor.cpp
)

target_include_directories(run_single_byte_xor_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_single_byte_xor_tests PRIVATE GTest::gtest_main)

add_test(NAME single_byte_xor_tests COMMAND run_single_byte_xor_tests)

# Test para Detect Single-Byte XOR
add_executable(run_detect_single_byte_xor_tests
    test_detect_single_byte_xor.cpp
    ${CMAKE_SOURCE_DIR}/src/detect_single_byte_xor.cpp
    ${CMAKE_SOURCE_DIR}/src/single_byte_xor.cpp
)

target_include_directories(run_detect_single_byte_xor_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_detect_single_byte_xor_tests PRIVATE GTest::gtest_main)

add_test(NAME detect_single_byte_xor_tests COMMAND run_detect_single_byte_xor_tests)

# Test para Repeating-Key XOR
add_executable(run_repeating_key_xor_tests
    test_repeating_key_xor.cpp
    ${CMAKE_SOURCE_DIR}/src/repeating_key_xor.cpp
)

target_include_directories(run_repeating_key_xor_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_repeating_key_xor_tests PRIVATE GTest::gtest_main)

add_test(NAME repeating_key_xor_tests COMMAND run_repeating_key_xor_tests)

# Test para Hamming Distance
add_executable(run_hamming_distance_tests
    test_hamming_distance.cpp
    ${CMAKE_SOURCE_DIR}/src/hamming_distance.cpp
)

target_include_directories(run_hamming_distance_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_hamming_distance_tests PRIVATE GTest::gtest_main)

add_test(NAME hamming_distance_tests COMMAND run_hamming_distance_tests)

# Test para Break Repeating-Key XOR
add_executable(run_break_repeating_key_xor_tests
    test_break_repeating_key_xor.cpp
    ${CMAKE_SOURCE_DIR}/src/break_repeating_key_xor.cpp
    ${CMAKE_SOURCE_DIR}/src/hamming_distance.cpp
    ${CMAKE_SOURCE_DIR}/src/single_byte_xor.cpp
)

target_include_directories(run_break_repeating_key_xor_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_break_repeating_key_xor_tests PRIVATE GTest::gtest_main OpenSSL::SSL OpenSSL::Crypto)

add_test(NAME break_repeating_key_xor_tests COMMAND run_break_repeating_key_xor_tests)

# Test para AES-ECB
add_executable(run_aes_ecb_tests
    test_aes_ecb.cpp
    ${CMAKE_SOURCE_DIR}/src/aes_ecb.cpp
)

target_include_directories(run_aes_ecb_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_aes_ecb_tests PRIVATE GTest::gtest_main OpenSSL::SSL OpenSSL::Crypto)

add_test(NAME aes_ecb_tests COMMAND run_aes_ecb_tests)

# Test para Detect ECB
add_executable(run_detect_ecb_tests
    test_detect_ecb.cpp
    ${CMAKE_SOURCE_DIR}/src/detect_ecb.cpp
)

target_include_directories(run_detect_ecb_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_detect_ecb_tests PRIVATE GTest::gtest_main)

add_test(NAME detect_ecb_tests COMMAND run_detect_ecb_tests)
