#include "muscle.h"
#include "../general_functions_and_variables/common_use_functions.h"

void muscle::init(double angle_gamma, double length_u, string muscle_name_) {
    muscle_name = muscle_name_;
    gamma = rad(angle_gamma);
    u = length_u*scale;
}

double muscle::calc_F(double F_N, double zeta) {
    F = get_gx(F_N);
    return (F*sin(omega)*u)/(sin(zeta)*l);
}

double muscle::get_gx(double F_N) {
    if (muscle_name == "peroneus") {
        // ax+b=y
        // return (6.9e1/5.90e2*F_N); // <-- f(x)

        // ax^2+bx+c=y
        double peroneus_F_N, zeta, omega_, F_peroneus_2, F_N_2, F_N_3, t;
        t = 6e-1;
        peroneus_F_N = 140 * t;
        zeta = rad(63);
        omega_ = rad(45);
        F_peroneus_2 = 69;
        F_N_2 = 590.0;
        F_N_3 = 1551.89;
        const double a = ((peroneus_F_N * sin(zeta) * l) / (sin(omega_) * u) - F_peroneus_2 * (F_N_3 / F_N_2)) /
                         (pow(F_N_3, 2) - pow(F_N_2, 2) * (F_N_3 / F_N_2));
        const double b = (F_peroneus_2 - a * pow(F_N_2, 2)) / F_N_2;
        const double c = pow(b, 2) / (4 * a); // c is x at g'(x) = 0
        return (a * pow(F_N, 2) + b * F_N + c); // <-- g(x)
    }
    else if (muscle_name == "flexor_hallucis_longus"){
        // ax+b=y
        return (4.3e1/2.95e2*F_N); // <-- f(x)
    }
    else if (muscle_name == "flexor_digitorum_longus"){
        // ax+b=y
        return (1.4e1/2.95e2*F_N); // <-- f(x)
    }
}
