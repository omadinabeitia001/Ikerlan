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

# Activar tests
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
)

add_library(crypto STATIC ${SET2_SRCS})
target_include_directories(crypto PUBLIC ${CMAKE_SOURCE_DIR}/../Set2/include)
target_link_libraries(crypto PUBLIC OpenSSL::SSL OpenSSL::Crypto)

# -----------------------
# Biblioteca pad_oracle_lib
# -----------------------
add_library(pad_oracle_lib
    src/padding_oracle.cpp
    src/utils_set3.cpp
    src/pkcs7_set3.cpp
    src/ctr_mode.cpp 
    src/ctr_breaker.cpp
    src/ctr_stats.cpp
    src/mt19937.cpp
    src/mt_cracker.cpp
    src/mt19937_clone.cpp
    src/mt_clone.cpp
    src/untemper.cpp
    src/mt_stream.cpp            # ← Añadido aquí
)
target_include_directories(pad_oracle_lib PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/../Set2/include)
target_link_libraries(pad_oracle_lib PUBLIC crypto)

# -----------------------
# Ejecutables
# -----------------------
add_executable(pad_oracle_main src/padding_oracle_main.cpp)
target_include_directories(pad_oracle_main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(pad_oracle_main PRIVATE pad_oracle_lib)

add_executable(ctr_mode_main src/ctr_mode_main.cpp)
target_include_directories(ctr_mode_main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(ctr_mode_main PRIVATE pad_oracle_lib)

add_executable(ctr_breaker_main src/ctr_breaker_main.cpp)
target_include_directories(ctr_breaker_main PRIVATE include)
target_link_libraries(ctr_breaker_main PRIVATE pad_oracle_lib)

add_executable(ctr_stats_main src/ctr_stats_main.cpp)
target_include_directories(ctr_stats_main PRIVATE include)
target_link_libraries(ctr_stats_main PRIVATE pad_oracle_lib)

add_executable(mt19937_main src/mt19937_main.cpp)
target_include_directories(mt19937_main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(mt19937_main PRIVATE pad_oracle_lib)

add_executable(mt_crack_main src/mt_crack_main.cpp src/mt_cracker.cpp)
target_include_directories(mt_crack_main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(mt_crack_main PRIVATE pad_oracle_lib)

add_executable(mt_clone_main src/mt_clone_main.cpp src/mt_clone.cpp)
target_include_directories(mt_clone_main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(mt_clone_main PRIVATE pad_oracle_lib)

add_executable(mt_stream_main src/mt_stream_main.cpp)        # ← Nuevo ejecutable
target_include_directories(mt_stream_main PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(mt_stream_main PRIVATE pad_oracle_lib)

# -----------------------
# Tests
# -----------------------
add_subdirectory(tests)
