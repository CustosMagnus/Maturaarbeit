#ifndef CODE_COMMON_USE_FUNCTIONS_H
#define CODE_COMMON_USE_FUNCTIONS_H

#include <string>
#include <vector>

using namespace std;

class s_vec {
private:
    void save_vector(std::vector<double> &vec, std::string name);
public:
    void save_all_vector(vector<vector<double>*>, vector<string>&);
};

void print(bool, double, double, double, double, double, unsigned int);

int file_length(const std::string &file_name);

double *read_file(const std::string &file_name, double *ar);

double rad(double deg);

double deg(double rad);

double get_poly_func_value(const std::vector<double> &vec, double x);

#endif //CODE_COMMON_USE_FUNCTIONS_H
