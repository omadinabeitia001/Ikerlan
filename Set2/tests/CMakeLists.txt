#  Tests para PKCS7
add_executable(run_pkcs7_tests test_pkcs7.cpp)
target_link_libraries(run_pkcs7_tests PRIVATE pkcs7 GTest::gtest_main)
add_test(NAME pkcs7_tests COMMAND run_pkcs7_tests)

#  Tests para CBC
add_executable(run_cbc_tests test_cbc.cpp)
target_link_libraries(run_cbc_tests PRIVATE cbc pkcs7 aes_ecb xor base64 GTest::gtest_main)
add_test(NAME cbc_tests COMMAND run_cbc_tests)

#  Tests para Oracle
add_executable(run_oracle_tests test_oracle.cpp)
target_link_libraries(run_oracle_tests PRIVATE oracle GTest::gtest_main pthread)
add_test(NAME OracleDetectionTest COMMAND run_oracle_tests)

#Test para BYTE ECB
add_executable(run_byte_ecb_tests test_byte_ecb.cpp)
target_link_libraries(run_byte_ecb_tests PRIVATE byte_ecb GTest::gtest_main)
add_test(NAME ByteECBTest COMMAND run_byte_ecb_tests)


# Test para ECB cut-and-paste
add_executable(run_ecb_cut_tests test_ecb_cut.cpp)
target_link_libraries(run_ecb_cut_tests PRIVATE ecb_cut GTest::gtest_main)
add_test(NAME ECBCutAndPasteTest COMMAND run_ecb_cut_tests)

#Test para byte ecb (hard)

add_executable(run_byte_ecb_hard_tests test_byte_ecb_hard.cpp)
target_link_libraries(run_byte_ecb_hard_tests PRIVATE byte_ecb_hard GTest::gtest_main)
add_test(NAME ByteECBHardTest COMMAND run_byte_ecb_hard_tests)

#Test para pkcs7 VALIDATION

add_executable(run_pkcs7_val_tests test_pkcs7_val.cpp)
target_link_libraries(run_pkcs7_val_tests PRIVATE pkcs7_val GTest::gtest_main)
add_test(NAME PKCS7ValTest COMMAND run_pkcs7_val_tests)

# Test cbc cbc_bitflip

add_executable(run_cbc_bitflip_tests test_cbc_bitflip.cpp)
target_link_libraries(run_cbc_bitflip_tests PRIVATE cbc_bitflip aes_cbc aes_ecb pkcs7_val pkcs7 utils GTest::gtest_main)
add_test(NAME CBCBitflipTest COMMAND run_cbc_bitflip_tests)