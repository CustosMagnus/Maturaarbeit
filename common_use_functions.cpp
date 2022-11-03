//
// Created by mcarl on 03/11/2022.
//

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

long double* read_file(const string &file_name, long double *ar) { // ar = long double ar[file_length(file)];
    int i = 0;
    string txt;
    ifstream file(file_name);
    while (getline(file, txt)) {
        ar[i] = stold(txt);
        i++;
    }
    file.close();
    return ar; // long double *res = read_file(ar);
}

double rad(double deg){ // changes degree to radians
    return (deg*(PI/180));
}

double deg(double rad){
    return (rad*(180/PI));
}

void save_vector(vector<double> &vec, string name){
    ofstream file(("c_results/"+ name));
    for (auto i = vec.begin(); i!=vec.end();++i) {
        file<<*i<<"\n";
    }
    file.close();
}

double get_poly_func_value(const vector<double> &vec, double x){ // vector contains all the coefficients of the function
    int n = 0; // (to the power of n)
    double res = 0;
    for(auto i=vec.begin();i!=vec.end();++i){
        res += *i * pow(x, n);
        n++;
    }
    return res;
}