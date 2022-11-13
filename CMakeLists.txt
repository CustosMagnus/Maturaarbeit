cmake_minimum_required(VERSION 3.23)
project(code)

set(CMAKE_CXX_STANDARD 20)

add_executable(code main.cpp general_functions_and_variables/calculate_coordinates.cpp general_functions_and_variables/calculate_coordinates.h general_functions_and_variables/common_use_functions.cpp general_functions_and_variables/common_use_functions.h unused_functions/find_stretching_factor.cpp unused_functions/find_stretching_factor.h general_functions_and_variables/extern_variables.h classes/ligament.h classes/muscle.h classes/ligament.cpp classes/muscle.cpp model1/model1.cpp model1/model1.h model1/run.cpp)
