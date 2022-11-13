cmake_minimum_required(VERSION 3.23)
project(code)

set(CMAKE_CXX_STANDARD 20)

add_executable(code main.cpp c_code/general_functions_and_variables/calculate_coordinates.cpp c_code/general_functions_and_variables/calculate_coordinates.h c_code/general_functions_and_variables/common_use_functions.cpp c_code/general_functions_and_variables/common_use_functions.h c_code/unused_functions/find_stretching_factor.cpp c_code/unused_functions/find_stretching_factor.h c_code/general_functions_and_variables/extern_variables.h c_code/classes/ligament.h c_code/classes/muscle.h c_code/classes/ligament.cpp c_code/classes/muscle.cpp c_code/model1/model1.cpp c_code/model1/model1.h c_code/model1/run.cpp c_code/classes/save.h c_code/classes/save.cpp c_code/dependency/dependency.h)
