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
