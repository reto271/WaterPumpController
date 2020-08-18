cmake_minimum_required(VERSION 2.6.4)
project(Test_WaterPumpController)

enable_testing()
add_subdirectory(googletest)

# Define compiler switches
set(CMAKE_CXX_FLAGS "-ggdb -g3 -Dgmock_build_tests=ON -D_UNIT_TESTS_ -Wall -std=c++17")
#set(CMAKE_CXX_FLAGS "-ggdb -g3 -Wall -std=c++17")

# This sets the output dir to /bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/..)
add_executable(Test_WaterPumpController
               src/main.cpp
               src/Test_DataTypeSize.cpp
               src/Test_IOHandler.cpp
               ../Application/IOHandler.cpp)

target_link_libraries(Test_WaterPumpController gtest_main gtest gmock)
