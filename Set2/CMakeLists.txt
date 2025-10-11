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

#utils

add_library(utils src/utils.cpp)
target_include_directories(utils PUBLIC include)


# BYTE ECB
add_library(byte_ecb src/byte_ecb.cpp)
target_include_directories(byte_ecb PUBLIC include)
target_link_libraries(byte_ecb PRIVATE pkcs7 aes_ecb base64 utils)



# 📦 ECB cut-and-paste
add_library(ecb_cut src/ecb_cut.cpp)
target_include_directories(ecb_cut PUBLIC include)
target_link_libraries(ecb_cut PRIVATE pkcs7 aes_ecb)

# BYTE ECB (hard)
add_library(byte_ecb_hard src/byte_ecb_hard.cpp)
target_include_directories(byte_ecb_hard PUBLIC include)
target_link_libraries(byte_ecb_hard PRIVATE pkcs7 aes_ecb base64 utils)

#PKCS7 VALIDATION
add_library(pkcs7_val src/pkcs7_val.cpp)
target_include_directories(pkcs7_val PUBLIC include)

# CBC bitflit
add_library(aes_cbc src/aes_cbc.cpp)
target_include_directories(aes_cbc PUBLIC include)

add_library(cbc_bitflip src/cbc_bitflip.cpp)
target_include_directories(cbc_bitflip PUBLIC include)
target_link_libraries(cbc_bitflip PRIVATE aes_cbc aes_ecb pkcs7_val pkcs7 utils)

# 🚀 Ejecutables
add_executable(pkcs7_main src/pkcs7_main.cpp)
target_link_libraries(pkcs7_main PRIVATE pkcs7)

add_executable(cbc_main src/cbc_main.cpp)
target_link_libraries(cbc_main PRIVATE cbc pkcs7 aes_ecb xor base64)

add_executable(oracle_main src/oracle_main.cpp)
target_link_libraries(oracle_main PRIVATE oracle)


add_executable(byte_ecb_main src/byte_ecb_main.cpp)
target_link_libraries(byte_ecb_main PRIVATE byte_ecb base64 utils pkcs7 aes_ecb)


add_executable(ecb_cut_main src/ecb_cut_main.cpp)
target_link_libraries(ecb_cut_main PRIVATE ecb_cut pkcs7 aes_ecb)

add_executable(byte_ecb_hard_main src/byte_ecb_hard_main.cpp)
target_link_libraries(byte_ecb_hard_main PRIVATE byte_ecb_hard)

add_executable(pkcs7_val_main src/pkcs7_val_main.cpp)
target_link_libraries(pkcs7_val_main PRIVATE pkcs7_val)

add_executable(cbc_bitflip_main src/cbc_bitflip_main.cpp)
target_link_libraries(cbc_bitflip_main PRIVATE cbc_bitflip aes_cbc aes_ecb pkcs7_val pkcs7 utils)