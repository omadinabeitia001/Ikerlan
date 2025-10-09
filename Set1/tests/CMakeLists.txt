cmake_minimum_required(VERSION 3.10)

# Encuentra GTest
find_package(GTest REQUIRED)

# Ejecutable de tests
add_executable(run_tests
    test_hex_to_base64.cpp
    ${CMAKE_SOURCE_DIR}/src/hex_to_base64.cpp
)

target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_tests PRIVATE GTest::gtest_main)

# Registro del test en CTest
add_test(NAME hex_to_base64_tests COMMAND run_tests)

# Ejecutable de tests para Fixed XOR
add_executable(run_fixed_xor_tests
    test_fixed_xor.cpp
    ${CMAKE_SOURCE_DIR}/src/fixed_xor.cpp
)

target_include_directories(run_fixed_xor_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_fixed_xor_tests PRIVATE GTest::gtest_main)

# Registro del test en CTest
add_test(NAME fixed_xor_tests COMMAND run_fixed_xor_tests)

# Ejecutable de tests para Single-byte XOR cipher
add_executable(run_single_byte_xor_tests
    test_single_byte_xor.cpp
    ${CMAKE_SOURCE_DIR}/src/single_byte_xor.cpp
)

target_include_directories(run_single_byte_xor_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_single_byte_xor_tests PRIVATE GTest::gtest_main)

# Registro del test en CTest
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

add_executable(run_repeating_key_xor_tests
    test_repeating_key_xor.cpp
    ${CMAKE_SOURCE_DIR}/src/repeating_key_xor.cpp
)

target_include_directories(run_repeating_key_xor_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(run_repeating_key_xor_tests PRIVATE GTest::gtest_main)

add_test(NAME repeating_key_xor_tests COMMAND run_repeating_key_xor_tests)
