#ifndef CODE_COMMON_USE_FUNCTIONS_H
#define CODE_COMMON_USE_FUNCTIONS_H

#include <string>
#include <vector>
#include "../classes/ligament.h"


using namespace std;

int file_length(const string &file_name);

void read_file(const string &file_name, vector<double> *ar);

double rad(double deg);

double deg(double rad);

double get_poly_func_value(const vector<double> &vec, double x);

void save_and_calculate_ligaments(ligament*, ligament*, ligament*, ligament*, const double);

#endif //CODE_COMMON_USE_FUNCTIONS_H
