#ifndef CODE_COMMON_USE_FUNCTIONS_H
#define CODE_COMMON_USE_FUNCTIONS_H

#include <string>
#include <vector>

int file_length(const std::string &file_name);

double *read_file(const std::string &file_name, double *ar);

double rad(double deg);

double deg(double rad);

void save_vector(std::vector<double> &vec, std::string name);

double get_poly_func_value(const std::vector<double> &vec, double x);

#endif //CODE_COMMON_USE_FUNCTIONS_H
