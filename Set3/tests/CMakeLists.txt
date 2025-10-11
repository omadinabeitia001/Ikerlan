# Test para Padding Oracle
add_executable(run_padding_oracle_tests test_padding_oracle.cpp)
target_link_libraries(run_padding_oracle_tests PRIVATE pad_oracle_lib GTest::gtest_main)
add_test(NAME PaddingOracleTest COMMAND run_padding_oracle_tests)

# Test para CTR Mode
add_executable(run_ctr_mode_tests test_ctr_mode.cpp)
target_link_libraries(run_ctr_mode_tests PRIVATE pad_oracle_lib GTest::gtest_main)
add_test(NAME CTRModeTest COMMAND run_ctr_mode_tests)

# Test para CTR Breaker
add_executable(run_ctr_breaker_tests test_ctr_breaker.cpp)
target_link_libraries(run_ctr_breaker_tests PRIVATE pad_oracle_lib GTest::gtest_main)
add_test(NAME CTRBreakerTest COMMAND run_ctr_breaker_tests)
