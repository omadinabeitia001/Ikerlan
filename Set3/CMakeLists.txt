cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0079 NEW)
project(Set3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencias
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

# Includes públicos/locales
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../Set2/include)
include_directories(${GTEST_INCLUDE_DIRS})

# Activar tests (el subdirectorio tests debe contener un CMakeLists.txt)
enable_testing()

# -----------------------
# Biblioteca 'crypto' (reutiliza fuentes de Set2)
# -----------------------
set(SET2_SRCS
    ${CMAKE_SOURCE_DIR}/../Set2/src/aes_cbc.cpp
    ${CMAKE_SOURCE_DIR}/../Set2/src/aes_ecb.cpp
    ${CMAKE_SOURCE_DIR}/../Set2/src/pkcs7.cpp
    ${CMAKE_SOURCE_DIR}/../Set2/src/pkcs7_val.cpp
    ${CMAKE_SOURCE_DIR}/../Set2/src/utils.cpp
    # añade aquí otros .cpp de Set2 que tu padding_oracle necesite
)

add_library(crypto STATIC ${SET2_SRCS})
target_include_directories(crypto PUBLIC ${CMAKE_SOURCE_DIR}/../Set2/include)
target_link_libraries(crypto PUBLIC OpenSSL::SSL OpenSSL::Crypto)

add_library(pad_oracle_lib
    src/padding_oracle.cpp
    src/utils_set3.cpp
    src/pkcs7_set3.cpp
    src/ctr_mode.cpp 
    src/ctr_breaker.cpp
)
target_include_directories(pad_oracle_lib PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/../Set2/include)
# pad_oracle_lib usa funciones AES/PKCS7 de la librería crypto
target_link_libraries(pad_oracle_lib PUBLIC crypto)

add_executable(pad_oracle_main
    src/padding_oracle_main.cpp
)
target_include_directories(pad_oracle_main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(pad_oracle_main PRIVATE pad_oracle_lib)


add_executable(ctr_mode_main
    src/ctr_mode_main.cpp
)
target_include_directories(ctr_mode_main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(ctr_mode_main PRIVATE pad_oracle_lib)

add_executable(ctr_breaker_main src/ctr_breaker_main.cpp)
target_include_directories(ctr_breaker_main PRIVATE include)
target_link_libraries(ctr_breaker_main PRIVATE pad_oracle_lib)



add_subdirectory(tests)
