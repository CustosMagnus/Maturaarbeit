//
// Created by mcarl on 03/11/2022.
//

#include "common_use_functions.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

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

double get_perp_f(double length, double angle, double force){
    return length*sin(angle)*force;
}