include(GoogleTest)
add_executable(tools_test
       read_parity_mat_test.cpp)

target_link_libraries(tools_test tools gtest_main)

add_test (tools_test tools_test)

