cmake_minimum_required(VERSION 3.23)
project(code)

set(CMAKE_CXX_STANDARD 20)

add_executable(code main.cpp calculate_coordinates.cpp calculate_coordinates.h common_use_functions.cpp common_use_functions.h find_stretching_factor.cpp find_stretching_factor.h extern_variables.h)
