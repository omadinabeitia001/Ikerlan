cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0079 NEW)
project(Set2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 🔍 Dependencias externas
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

# 📁 Includes
include_directories(include)
include_directories(${GTEST_INCLUDE_DIRS})

# 🧪 Activar tests
enable_testing()
add_subdirectory(tests)

# 📦 Librerías base
add_library(pkcs7 src/pkcs7.cpp)
target_include_directories(pkcs7 PUBLIC include)

add_library(xor src/xor.cpp)
target_include_directories(xor PUBLIC include)

add_library(base64 src/base64.cpp)
target_include_directories(base64 PUBLIC include)
target_link_libraries(base64 PUBLIC OpenSSL::Crypto)

add_library(aes_ecb src/aes_ecb.cpp)
target_include_directories(aes_ecb PUBLIC include)
target_link_libraries(aes_ecb PUBLIC OpenSSL::Crypto)

# 📦 CBC
add_library(cbc src/cbc.cpp)
target_include_directories(cbc PUBLIC include)
target_link_libraries(cbc PRIVATE aes_ecb pkcs7 xor)

# 📦 Oracle
add_library(oracle src/oracle.cpp)
target_include_directories(oracle PUBLIC include)
target_link_libraries(oracle PRIVATE aes_ecb cbc pkcs7 xor)

# 🚀 Ejecutables
add_executable(pkcs7_main src/pkcs7_main.cpp)
target_link_libraries(pkcs7_main PRIVATE pkcs7)

add_executable(cbc_main src/cbc_main.cpp)
target_link_libraries(cbc_main PRIVATE cbc pkcs7 aes_ecb xor base64)

add_executable(oracle_main src/oracle_main.cpp)
target_link_libraries(oracle_main PRIVATE oracle)

