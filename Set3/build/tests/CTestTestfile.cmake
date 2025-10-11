# CMake generated Testfile for 
# Source directory: /home/student/Ikerlan/Set3/tests
# Build directory: /home/student/Ikerlan/Set3/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(PaddingOracleTest "/home/student/Ikerlan/Set3/build/tests/run_padding_oracle_tests")
set_tests_properties(PaddingOracleTest PROPERTIES  _BACKTRACE_TRIPLES "/home/student/Ikerlan/Set3/tests/CMakeLists.txt;4;add_test;/home/student/Ikerlan/Set3/tests/CMakeLists.txt;0;")
add_test(CTRModeTest "/home/student/Ikerlan/Set3/build/tests/run_ctr_mode_tests")
set_tests_properties(CTRModeTest PROPERTIES  _BACKTRACE_TRIPLES "/home/student/Ikerlan/Set3/tests/CMakeLists.txt;9;add_test;/home/student/Ikerlan/Set3/tests/CMakeLists.txt;0;")
add_test(CTRBreakerTest "/home/student/Ikerlan/Set3/build/tests/run_ctr_breaker_tests")
set_tests_properties(CTRBreakerTest PROPERTIES  _BACKTRACE_TRIPLES "/home/student/Ikerlan/Set3/tests/CMakeLists.txt;14;add_test;/home/student/Ikerlan/Set3/tests/CMakeLists.txt;0;")
