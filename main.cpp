#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <assert.h>
#include <vector>
#include "common_use_functions.h"
#include "calculate_coordinates.h"

using namespace std;

// scale from geogebra file to real distance
const double scale = 1.0;

double get_poly_func_value(double *coef_ar[], unsigned int &x){

}

class ligament {
public: // variables
    // lengths
    double l, r;
    // angle in rad
    double alpha, betta;
    // strain in N
    double Fx;
    // vektor with all Fx
    vector<double> v_Fx;
public: // functions
    ligament(double, double, double, double ); // constructor
};
ligament::ligament(double length_l, double length_r, // constructor
                   double alpha_l, double betta_r){
    assert(length_r>0); assert(length_r>0); assert(alpha_l>0); assert(betta_r>0);
    l = length_l*scale;
    r = length_r*scale;
    alpha = rad(alpha_l);
    betta = rad(betta_r);
}

void model1(){
    const double dt = 2.5e-3;
    const double t_start = 8.955;
    const string k_file = "data_kraftmessplatte.txt";
    const unsigned int k_len = file_length(k_file);
    const double mu_coef_ar[2] = {1e0, 2e0};

    // names are taken from the geogebra file
    long double F_Achillessehne; double mu; double r = 17.41; double M_A; // r = r0 from geogebra file
    long double F_N; double zeta; double l = 57.07; double M_N; // l = l1 from geogebra file
    l *= scale;
    r *= scale;


    ligament x1(57.07,20.54,20.46,76.21);


    long double ar[k_len];
    long double *data = read_file(k_file, ar);
    const long double tare = sqrt(pow(*data, 2)); // tare = |data[0]|

    x1.v_Fx.resize(k_len, 0);

    for (unsigned int t_steps=0;t_steps<k_len;t_steps++){
        zeta = rad(63.69);
        mu = rad(5);

        F_N = *(data+t_steps)+tare;
        if (F_N<0){F_N = 0;} // because there should be no negative force
        M_N = F_N*sin(zeta)*l;
        F_Achillessehne = M_N/(sin(mu)*r);
        M_A = sin(mu)*r*F_Achillessehne;

        x1.Fx = (M_A-M_N)/(x1.r*sin(x1.betta)-x1.l*sin(x1.alpha));
        x1.v_Fx[t_steps] = x1.Fx;

        cout<<"An t="<<t_start+dt*t_steps<<
            "\nAchillessehne: "<<F_Achillessehne<<
            "\nAponeurosis plantaris: "<<x1.Fx<<endl<<endl;
    }
}


int main() {
    model1();
}
