#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
#include <vector>
#include "common_use_functions.h"

using namespace std;

// scale from geogebra file to real distance
const double scale = 1.0;

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
    ligament(double, double, double, double); // constructor
};

ligament::ligament(double length_l, double length_r, // constructor
                   double alpha_l, double betta_r) {
    assert(length_r > 0);
    assert(length_r > 0);
    assert(alpha_l > 0);
    assert(betta_r > 0);
    l = length_l * scale;
    r = length_r * scale;
    alpha = rad(alpha_l);
    betta = rad(betta_r);
}

void model1() {
    const double dt = 2.5e-3;
    const double t_start = 8.955;
    const string k_file = "data_kraftmessplatte.txt";
    const unsigned int k_len = file_length(k_file);
    /*
    mu(x) =
     - 0.000000073965086042179900000000x^6
     + 0.000017266928022563500000000000x^5
     - 0.001559838172237700000000000000x^4
     + 0.067667051084868000000000000000x^3
     - 1.356168240929040000000000000000x^2
     + 8.884185993272690000000000000000x
     + 61.465602945187100000000000000000
    */
    const vector<double> v_mu_coef{
            61.465602945187100000000000000000,
            8.884185993272690000000000000000,
            -1.356168240929040000000000000000,
            0.067667051084868000000000000000,
            -0.001559838172237700000000000000,
            0.000017266928022563500000000000,
            -0.000000073965086042179900000000,
    };
    /*
    zeta(x) =
     + 0.000000073883780064143600000000x^6
     - 0.000017388468992470000000000000x^5
     + 0.001564922033964860000000000000x^4
     - 0.066567091301266100000000000000x^3
     + 1.284791261801270000000000000000x^2
     - 7.582514921559780000000000000000x
     + 36.272397750079100000000000000000

    */
    const vector<double> v_zeta_coef{
            36.272397750079100000000000000000,
            -7.582514921559780000000000000000,
            1.284791261801270000000000000000,
            -0.066567091301266100000000000000,
            0.001564922033964860000000000000,
            -0.000017388468992470000000000000,
            0.00000007388378006414360000000,
    };

    // names are taken from the geogebra file
    double F_Achillessehne;
    double mu;
    double r = 17.41;
    double M_A; // r = r0 from geogebra file
    vector<double> v_F_Achillessehne;
    v_F_Achillessehne.resize(k_len, 0);
    double F_N;
    double zeta;
    double l = 57.07;
    double M_N; // l = l1 from geogebra file
    vector<double> v_F_N;
    v_F_N.resize(k_len, 0);
    vector<double> v_zeta(k_len, 0), v_mu(k_len, 0);
    l *= scale;
    r *= scale;


    ligament x1(57.07, 20.54, 20.46, 76.21);


    double ar[k_len];
    double *data = read_file(k_file, ar);
    const double tare = sqrt(pow(*data, 2)); // tare = |data[0]|

    for (unsigned int t_steps = 0; t_steps < k_len; t_steps++) {
        zeta = rad(get_poly_func_value(v_zeta_coef, t_steps));
        mu = rad(get_poly_func_value(v_mu_coef, t_steps));

        F_N = (*(data + t_steps) + tare)/2; // weil 2 füsse
        if (F_N < 0) { F_N = 0; } // because there should be no negative force
        M_N = F_N * sin(zeta) * l;
        cout << sin(zeta) << endl;
        F_Achillessehne = M_N / (sin(mu) * r);
        M_A = sin(mu) * r * F_Achillessehne;
        assert(M_A >= 0 && F_Achillessehne >= 0 && M_N >= 0);

        x1.Fx = (M_A - M_N) / (x1.r * sin(x1.betta) - x1.l * sin(x1.alpha));

        // save data
        v_mu[t_steps] = mu;
        v_zeta[t_steps] = zeta;
        v_F_Achillessehne[t_steps] = F_Achillessehne;
        v_F_N[t_steps] = F_N;
        x1.v_Fx.push_back(x1.Fx);

        cout << "An t=" << t_start + dt * t_steps <<
             "\nF_N: " << F_N <<
             "\nAchillessehne: " << F_Achillessehne <<
             "\nAponeurosis plantaris: " << x1.Fx << endl << endl;
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
