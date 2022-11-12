#include <iostream>
#include <string>
#include <cmath>
#include <cassert>
#include <vector>
#include "extern_variables.h"
#include "common_use_functions.h"
#include "calculate_coordinates.h"
#include "muscle.h"
#include "ligament.h"

using namespace std;

void model1() {
    s_vec save;
    double F; /* total force on all Ligaments */
    double h_on_floor = 0; // Force at the moment the foot touches the floor
    bool h_on_floor_check;
    const double dt = 2.5e-3;
    const string k_file = "data_kraftmessplatte.txt";
    const unsigned int k_len = file_length(k_file);

    // names are taken from the geogebra file
    double F_Achillessehne;
    double mu;
    double r = 21.12854; // r = r0 from geogebra file
    double M_A;
    vector<double> v_F_Achillessehne;
    v_F_Achillessehne.resize(k_len, 0);
    double F_N;
    double zeta;
    double l = 57.07347; // l = l1 from geogebra file
    double M_N;
    vector<double> v_F_N;
    v_F_N.resize(k_len, 0);
    vector<double> v_zeta(k_len, 0), v_mu(k_len, 0);
    l *= scale;
    r *= scale;

    ligament x1(57.07347, 20.54411, 20.46205, 76.21216, 0.25);
    ligament x2(31.95423,20.54411,36.2549,66.90092,0.25);
    ligament x3(19.46833,15.10836,50.22875,82.05809,0.25);
    ligament x4(14.95728,11.53488,40.95749,121.78992,0.25);

    muscle peroneus(6.73575, 500, 6.59942);

    // check if the sum of all the proportions x = 1
    assert(x1.x+x2.x+x3.x+x4.x==1);

    double ar[k_len];
    double *data = read_file(k_file, ar);
    const double tare = sqrt(pow(*data, 2)); // tare = |data[0]|

    for (unsigned int t_steps = 0; t_steps < k_len; t_steps++) {
        zeta = rad(get_poly_func_value(v_zeta_coef, t_steps));
        mu = rad(get_poly_func_value(v_mu_coef, t_steps));
        peroneus.omega = mu - peroneus.gamma; // angle between u and F_Achillessehne

        v_F_N[t_steps] = F_N = (*(data + t_steps) + tare) / 2; // weil 2 füsse
        if (F_N < 0) { F_N = 0; } // because there should be no negative force
        /*
         if heel is not on the floor
         zeta = 62.2° -> point where the heel starts to touch the spieth roll
         zeta = 69 the heel is completley putting pressure on the plate
        */
        if (zeta <= rad(69.0)) {
            h_on_floor_check = false;
            M_N = (F_N - peroneus.calc_F(F_N, zeta, l)) * sin(zeta) * l;
        } else { // if heel is on the floor
            if (h_on_floor == 0) {
                h_on_floor = F_N - peroneus.calc_F(F_N, zeta, l);
            }
            h_on_floor_check = true;
            M_N = h_on_floor * sin(zeta) * l;
        }

        v_F_Achillessehne[t_steps] = F_Achillessehne = M_N / (sin(mu) * r);
        M_A = sin(mu) * r * F_Achillessehne;

        // calculate F which is the sum of all strains in x_n
        F = M_A / (x1.x * x1.r * sin(x1.betta) +
                   x2.x * x2.r * sin(x2.betta) +
                   x3.x * x3.r * sin(x3.betta) +
                   x4.x * x4.r * sin(x4.betta));


        // save data
        {
            v_mu[t_steps] = deg(mu);
            v_zeta[t_steps] = deg(zeta);
            // calculate and save Fx
            x1.v_Fx.push_back(x1.get_Fx(F));
            x2.v_Fx.push_back(x2.get_Fx(F));
            x3.v_Fx.push_back(x3.get_Fx(F));
            x4.v_Fx.push_back(x4.get_Fx(F));
            peroneus.v_F.push_back(peroneus.F);
        }

        // print the output
        print(h_on_floor_check, dt, F_N, F_Achillessehne, x1.Fx, peroneus.F, t_steps);
    }
    // write to file
    vector<vector<double>*> vec_val{&peroneus.v_F, &v_F_N, &v_F_Achillessehne, &v_mu, &v_zeta, &x1.v_Fx, &x2.v_Fx, &x3.v_Fx, &x4.v_Fx};
    vector<string> vec_name{"Peroneus.txt", "F_N.txt", "F_Achillessehne.txt", "mu_calculated.txt", "zeta_calculated.txt",
    "Aponeurosis_plantaris.txt", "Plantare_longum.txt", "Calcaneocuboideum_plantare.txt", "Calcaneonaviculare_plantare.txt"};
    save.save_all_vector(vec_val, vec_name);
}

int main() {
    calculate_angles_from_coordinates();
    model1();
}
