#ifndef CODE_COMMON_USE_FUNCTIONS_H
#define CODE_COMMON_USE_FUNCTIONS_H

#include <string>
#include <vector>
#include "ligament.h"

using namespace std;

class s_vec {
private:
    void save_vector(vector<double> &vec, string name);
public:
    void save_all_vector(vector<vector<double>*>, vector<string>&);
};

void print(bool, double, double, double, double, double, unsigned int);

int file_length(const string &file_name);

double *read_file(const string &file_name, double *ar);

double rad(double deg);

double deg(double rad);

double get_poly_func_value(const vector<double> &vec, double x);

void save_and_calculate_ligaments(ligament*, ligament*, ligament*, ligament*, const double);

#endif //CODE_COMMON_USE_FUNCTIONS_H
