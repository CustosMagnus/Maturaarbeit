#include <cassert>
#include "../general_functions_and_variables/common_use_functions.h"
#include "../general_functions_and_variables/extern_variables.h"
#include "ligament.h"

using namespace std;

ligament::ligament(double length_l, double length_r, // constructor
                   double alpha_l, double betta_r, string lig_name_) {
    lig_name = lig_name_;
    assert(length_l > 0);
    assert(length_r > 0);
    assert(alpha_l > 0);
    assert(betta_r > 0);
    x = get_proportion();
    cout<<lig_name<<" "<<x<<endl<<endl;
    l = length_l * scale;
    r = length_r * scale;
    alpha = rad(alpha_l);
    betta = rad(betta_r);
}

double ligament::get_Fx(double F){
    Fx = F * x;
    return Fx;
}

double ligament::get_proportion() const {
    // diameter in mm^2 of the corresponding ligament (real value is only known for x0 and x3)
    double l_x0 = 69.2, l_x1, l_x2, l_x3 = 24.5; // 33.85
    l_x1 = l_x3 * 1.1e0;
    l_x2 = l_x3 * 5.0e-1;
    if (lig_name == "aponeurosis_plantaris"){
        return (l_x0)/(l_x0+l_x1+l_x2+l_x3);
    }
    else if (lig_name == "plantare_longum"){
        return (l_x1)/(l_x0+l_x1+l_x2+l_x3);
    }
    else if (lig_name == "calcaneocuboideum_plantare"){
        return (l_x2)/(l_x0+l_x1+l_x2+l_x3);
    }
    else if (lig_name == "calcaneonaviculare_plantare"){
        return (l_x3)/(l_x0+l_x1+l_x2+l_x3);
    }
}
