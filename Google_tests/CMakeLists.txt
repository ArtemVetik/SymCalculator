# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'test1.cpp tests2.cpp' are source files with tests
#add_executable(Google_Tests_run test1.cpp tests2.cpp)
target_link_libraries(SymCalculator gtest gtest_main)