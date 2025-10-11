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

# Test para CTR Stats
add_executable(run_ctr_stats_tests test_ctr_stats.cpp)
target_link_libraries(run_ctr_stats_tests PRIVATE pad_oracle_lib GTest::gtest_main)
add_test(NAME CTRStatsTest COMMAND run_ctr_stats_tests)

# Test para MT19937
add_executable(run_mt19937_tests test_mt19937.cpp)
target_link_libraries(run_mt19937_tests PRIVATE pad_oracle_lib GTest::gtest_main)
add_test(NAME MT19937Test COMMAND run_mt19937_tests)

# Test para MT cracker
add_executable(run_mt_cracker_tests test_mt_cracker.cpp)
target_link_libraries(run_mt_cracker_tests PRIVATE pad_oracle_lib GTest::gtest_main)
add_test(NAME MTCrackerTest COMMAND run_mt_cracker_tests)

# Test para MT Clone
add_executable(run_mt_clone_tests test_mt_clone.cpp)
target_link_libraries(run_mt_clone_tests PRIVATE pad_oracle_lib GTest::gtest_main)
add_test(NAME MTCloneTest COMMAND run_mt_clone_tests)

# Test para MT Stream Cipher
add_executable(run_mt_stream_tests test_mt_stream.cpp)
target_link_libraries(run_mt_stream_tests PRIVATE pad_oracle_lib GTest::gtest_main)
add_test(NAME MTStreamTest COMMAND run_mt_stream_tests)
