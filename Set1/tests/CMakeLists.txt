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
