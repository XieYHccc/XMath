cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(XMath VERSION 0.0)
message(STATUS "[Project] ${PROJECT_NAME}") 

set(CMAKE_CXX_STANDARD 20)

option(XMATH_BUILD_TEST "Build test" ON)

if(XMATH_BUILD_TEST)
    add_subdirectory(test)
endif()