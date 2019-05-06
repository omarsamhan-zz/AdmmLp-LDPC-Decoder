cmake_minimum_required (VERSION 3.2)

set (CMAKE_CXX_STANDARD 11)

set (project_name admmlp_ldpc_decoder)

project (project_name)

include_directories (googletest/googletest/include/)

add_subdirectory (tools)

enable_testing()
if(test)
    add_subdirectory (test/tools)
    add_test(NAME that-test-I-made COMMAND runUnitTests)
endif()
