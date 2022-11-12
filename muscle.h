#ifndef CODE_MUSCLE_H
#define CODE_MUSCLE_H

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include "common_use_functions.h"
#include "extern_variables.h"

using namespace std;

class muscle {
public: // variables
    // current force in N
    double F;
    // max force in N
    double F_max;
    // length of u
    double u;
    // angle between u and r0
    double gamma;
    // angle to achilles tendom
    double omega;
    // vektor with all F
    vector<double> v_F;
public: // functions
    muscle(double, double, double);
    double calc_F(double, double, double);
};

muscle::muscle(double angle_gamma, double F_max_, double length_u) {
    gamma = rad(angle_gamma);
    F_max = F_max_;
    u = length_u*scale;
}

double muscle::calc_F(double F_N, double zeta, double l) {
    F = (6.9e1/5.90e2*F_N);
    if (F>F_max){ // because you can't move more than you have the force to do so
        F = F_max;
    }
    return (F*sin(omega)*u)/(sin(zeta)*l);
}

#endif //CODE_MUSCLE_H
