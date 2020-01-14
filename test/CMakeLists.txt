cmake_minimum_required(VERSION 2.6)

include(GoogleTest)
include_directories(${GTEST_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)

add_executable(metadata_tests metadata_tests.cpp ${PROJECT_SOURCE_DIR}/src/metadata.cpp)
target_link_libraries(metadata_tests gtest gtest_main pthread)
add_test(NAME metadata_tests COMMAND metadata_tests)
