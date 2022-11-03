#include <iostream>
#include <string>
#include <cmath>
#include <assert.h>
#include <vector>
#include "common_use_functions.h"
#include "calculate_coordinates.h"

using namespace std;

// scale from geogebra file to real distance
const double scale = 1.0;


double shift_for_poly_func(unsigned int t_picture){
    double t_p = t_picture;
    double t_f = 0e0;

    return t_f;
}


class ligament {
public: // variables
    // lengths
    double l, r;
    // angle in rad
    double alpha, betta;
    // forces on each end
    double Fxl, Fxr;
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
    // mu(x) = -7E-08x^6 + 2E-05x^5 - 0.0016x^4 + 0.0677x^3 - 1.3562x^2 + 8.8842x + 61.466
    const vector<double> v_mu_coef{61.466, 8.8842, -1.3562, 0.0677, -0.0016, 2e-5, -7e-8};
    // zeta(x) = 7E-08x^6 - 2E-05x^5 + 0.0016x^4 - 0.0666x^3 + 1.2848x^2 - 7.5825x + 36.272
    const vector<double> v_zeta_coef{36.272, -7.5825, 1.2848, -0.0666, 0.0016, -2e-5, 7e-8};

    // names are taken from the geogebra file
    double F_Achillessehne; double mu; double r = 17.41; double M_A; // r = r0 from geogebra file
    vector<double> v_F_Achillessehne; v_F_Achillessehne.resize(k_len, 0);
    double F_N; double zeta; double l = 57.07; double M_N; // l = l1 from geogebra file
    vector<double> v_F_N; v_F_N.resize(k_len, 0);
    vector<double> v_zeta(k_len, 0), v_mu(k_len, 0);
    l *= scale;
    r *= scale;


    ligament x1(57.07,20.54,20.46,76.21);


    long double ar[k_len];
    long double *data = read_file(k_file, ar);
    const long double tare = sqrt(pow(*data, 2)); // tare = |data[0]|

    for (unsigned int t_steps=0;t_steps<k_len;t_steps++){
        zeta = get_poly_func_value(v_zeta_coef, shift_for_poly_func(t_steps));
        mu = get_poly_func_value(v_mu_coef, shift_for_poly_func(t_steps));

        F_N = *(data+t_steps)+tare;
        if (F_N<0){F_N = 0;} // because there should be no negative force
        M_N = F_N*sin(zeta)*l;
        F_Achillessehne = M_N/(sin(mu)*r);
        M_A = sin(mu)*r*F_Achillessehne;

        x1.Fx = (M_A-M_N)/(x1.r*sin(x1.betta)-x1.l*sin(x1.alpha));

        // save data
        v_mu[t_steps] = mu;
        v_zeta[t_steps] = zeta;
        v_F_Achillessehne[t_steps] = F_Achillessehne;
        v_F_N[t_steps] = F_N;
        x1.v_Fx.push_back(x1.Fx);

        cout<<"An t="<<t_start+dt*t_steps<<
            "\nAchillessehne: "<<F_Achillessehne<<
            "\nAponeurosis plantaris: "<<x1.Fx<<endl<<endl;
    }
    save_vector(v_F_N, "F_N.txt");
    save_vector(v_F_Achillessehne, "F_Achillessehne.txt");
    save_vector(x1.v_Fx, "Aponeurosis_plantaris.txt");
    save_vector(v_mu, "mu_calculated.txt");
    save_vector(v_zeta, "zeta_calculated.txt");
}


int main() {
    model1();
}
