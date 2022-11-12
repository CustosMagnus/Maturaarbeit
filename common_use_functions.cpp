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

double get_poly_func_value(const vector<double> &vec, double x) { // vector contains all the coefficients of the function
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

void print(bool h_on_floor_check, double dt, double F_N, double F_Achillessehne, double x1_Fx, double pF, unsigned int t_steps){
    if (h_on_floor_check) {
        cout << "Ferse ist auf dem Boden" << endl;
    } else {
        cout << "Ferse ist nicht auf dem Boden" << endl;
    }
    cout << "An t=" << dt * t_steps <<
         "\nF_N: " << F_N <<
         "N\nAchillessehne: " << F_Achillessehne <<
         "N\nAponeurosis plantaris: " << x1_Fx <<
         "N\nPeroneus: " << pF <<
         "N\n";
}

// s_vec Class
void s_vec::save_vector(vector<double> &vec, const string name) {
    ofstream file(("c_results/" + name));
    for (auto i: vec) {
        file << i << "\n";
    }
    file.close();
}

void s_vec::save_all_vector(vector<vector<double>*> vec_val, vector<string> &vec_name){
    for (int i = 0; i < vec_name.size(); i++){
        save_vector(*vec_val[i], vec_name[i]);
    }
}

void save_and_calculate_ligaments(ligament *x0, ligament *x1, ligament *x2, ligament *x3, const double F){
    x0->v_Fx.push_back(x0->get_Fx(F));
    x1->v_Fx.push_back(x1->get_Fx(F));
    x2->v_Fx.push_back(x2->get_Fx(F));
    x3->v_Fx.push_back(x3->get_Fx(F));
}