#include "muscle.h"
#include "../general_functions_and_variables/common_use_functions.h"


void muscle::init(double angle_gamma, double length_u) {
    gamma = rad(angle_gamma);
    u = length_u*scale;
}

double muscle::calc_F(double F_N, double zeta) {
    // F = (6.9e1/5.90e2*F_N); // <-- f(x)
    F = get_gx(F_N);
    if (F<0){F=0;}
    return (F*sin(omega)*u)/(sin(zeta)*l);
}

double muscle::get_gx(double F_N) {
    double peroneus_F_N, zeta, omega_, F_peroneus_2, F_N_2, F_N_3, t;
    t = 9e-1;
    peroneus_F_N = 140 * t;
    zeta = rad(63);
    omega_ = rad(45);
    F_peroneus_2 = 69;
    F_N_2 = 590.0;
    F_N_3 = 1551.89;
    const double a = ((peroneus_F_N*sin(zeta)*l)/(sin(omega_)*u)-F_peroneus_2*(F_N_3/F_N_2))/(pow(F_N_3,2)-pow(F_N_2,2)*(F_N_3/F_N_2));
    const double b = (F_peroneus_2-a*pow(F_N_2,2))/F_N_2;
    const double c = 0;
    return (a*pow(F_N, 2)+b*F_N+c);
}
