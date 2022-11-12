#include "muscle.h"


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