include(GoogleTest)
add_executable(tools_test
       read_parity_mat_test.cpp)

# gtest_add_tests(TARGET      FooTest
#       TEST_SUFFIX .noArgs
#       TEST_LIST   noArgsTests
#)

# add_library (tools_test )

target_include_directories(tootle_test tools)
