# Root cmake file

cmake_minimum_required (VERSION 3.2)

set (CMAKE_CXX_STANDARD 11)

set (project_name admmlp_ldpc_decoder)

project (project_name)

add_subdirectory (tools)

enable_testing()

add_subdirectory (test/tools)
add_subdirectory (ext_libs/googletest)
