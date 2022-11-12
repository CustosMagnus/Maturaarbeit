#ifndef CODE_LIGAMENT_H
#define CODE_LIGAMENT_H

#include <iostream>
#include <vector>
#include <cassert>
#include "common_use_functions.h"
#include "extern_variables.h"

using namespace std;

class ligament {
public: // variables
    // lengths
    double l, r;
    // angle in rad
    double alpha, betta;
    // proportion to the other ligaments
    double x;
    // strain in N
    double Fx;
    // vektor with all Fx
    vector<double> v_Fx;
public: // functions
    ligament(double, double, double, double, double); // constructor
    double get_Fx(double);
};

ligament::ligament(double length_l, double length_r, // constructor
                   double alpha_l, double betta_r, double proportion_x) {
    assert(length_l > 0);
    assert(length_r > 0);
    assert(alpha_l > 0);
    assert(betta_r > 0);
    assert(0<proportion_x && 1>proportion_x);
    x = proportion_x;
    l = length_l * scale;
    r = length_r * scale;
    alpha = rad(alpha_l);
    betta = rad(betta_r);
}

double ligament::get_Fx(double F){
    Fx = F * x;
    return Fx;
}

#endif //CODE_LIGAMENT_H
