#ifndef CODE_LIGAMENT_H
#define CODE_LIGAMENT_H

#include <iostream>
#include <vector>
#include <cassert>
#include "../general_functions_and_variables/common_use_functions.h"
#include "../general_functions_and_variables/extern_variables.h"

using namespace std;

class ligament : general_var{
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

#endif //CODE_LIGAMENT_H
