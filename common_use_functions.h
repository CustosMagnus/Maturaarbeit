//
// Created by mcarl on 03/11/2022.
//

#ifndef CODE_COMMON_USE_FUNCTIONS_H
#define CODE_COMMON_USE_FUNCTIONS_H

#include <string>
int file_length(const std::string &file_name);
long double* read_file(const std::string &file_name, long double *ar);
double rad(double deg);
double deg(double rad);
double get_perp_f(double length, double angle, double force);

#endif //CODE_COMMON_USE_FUNCTIONS_H
