# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (LimitOrderBook)
set (CMAKE_CXX_STANDARD 23)


# set(SOURCES
#     src/OrderBook.cpp
#      src/Limit.cpp
#     src/LimitContainer.cpp
#     src/main.cpp
# )

add_library(library STATIC 
src/OrderBook.cpp
src/Limit.cpp
src/LimitContainer.cpp
)

find_package(benchmark REQUIRED)


# Add an executable with the above sources
# add_executable(LOB ${SOURCES})


# set(TEST
#     src/OrderBook.cpp
#     src/Limit.cpp
#     src/LimitContainer.cpp
#     Test/LOBtest.cpp)

add_executable(LOB src/main.cpp)
target_link_libraries(LOB library)



add_executable(LOB_test  Test/LOBtest.cpp)
target_link_libraries(LOB_test library)
target_link_libraries(LOB_test benchmark::benchmark)

target_include_directories(library
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(LOB
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)


# # Add an executable with the above sources
# add_executable(LOB_test ${TEST})

target_include_directories(LOB_test
PRIVATE 
    ${PROJECT_SOURCE_DIR}/include)

# add_test(test_build LOB_test)



# add_test(test_build
#   "${CMAKE_COMMAND}"
#   --build "${CMAKE_BINARY_DIR}"
#   --config "$<CONFIG>"
#   --target LOB_test
# )
# set_tests_properties(test_build PROPERTIES FIXTURES_SETUP    test_fixture)
# add_test(test test)
# set_tests_properties(test       PROPERTIES FIXTURES_REQUIRED test_fixture)

## valgrind
# find_program(CTEST_MEMORYCHECK_COMMAND NAMES valgrind)
# INCLUDE(Dart)