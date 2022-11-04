#include "common_use_functions.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const double PI = 3.14159265358979323846;

int file_length(const string &file_name) { // returns number of lines in a file
    ifstream file(file_name);
    int i = 0;
    string txt;
    while (getline(file, txt)) {
        i++;
    }
    file.close();
    return i;
}

double *read_file(const string &file_name, double *ar) { // ar = double ar[file_length(file)];
    int i = 0;
    string txt;
    ifstream file(file_name);
    while (getline(file, txt)) {
        ar[i] = stod(txt);
        i++;
    }
    file.close();
    return ar; // long double *res = read_file(ar);
}

double rad(double deg) { // changes degree to radians
    return (deg * (PI / 180));
}

double deg(double rad) {
    return (rad * (180 / PI));
}

void save_vector(vector<double> &vec, const string name) {
    ofstream file(("c_results/" + name));
    for (auto i: vec) {
        file << i << "\n";
    }
    file.close();
}

double
get_poly_func_value(const vector<double> &vec, double x) { // vector contains all the coefficients of the function
    int n = 0; // (to the power of n)
    double res = 0;
    double a = 1.2e0; // 0.0025/(1/480)
    double b = 7.4; // 11-1.2*3
    x = a * x + b; // adapt to the other x scale
    for (auto i: vec) {
        res += i * pow(x, n);
        n++;
    }
    return res;
}