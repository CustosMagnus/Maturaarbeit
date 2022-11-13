#ifndef CODE_MUSCLE_H
#define CODE_MUSCLE_H

#include "../dependency/dependency.h"
#include "../general_functions_and_variables/common_use_functions.h"
#include "../general_functions_and_variables/extern_variables.h"

using namespace std;

class muscle : general_var {
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
    void init(double, double, double);
    double calc_F(double, double, double);
};

#endif //CODE_MUSCLE_H