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

class model1 {
public:
    // ligaments
    vector<ligament> lig;
    // muscle
    muscle peroneus;
    double F; // total force on all Ligaments
    // files
    s_vec save;
    const string k_file = "data_kraftmessplatte.txt";
    const unsigned int k_len = file_length(k_file);
    // get data
    vector<double> data;
    double tare; // tare = |data[0]|
    // time
    const double dt = 2.5e-3;
    // heel on floor
    double h_on_floor = 0; // Force at the moment the foot touches the floor
    bool h_on_floor_check;
    // names are taken from the geogebra file
    // backside of the foot
    double F_Achillessehne;
    double mu;
    double r = 21.12854; // r = r0 from geogebra file
    double M_A;
    vector<double> v_F_Achillessehne, v_mu;
    // frontside of the foot
    double F_N;
    double zeta;
    double l = 57.07347; // l = l1 from geogebra file
    double M_N;
    vector<double> v_F_N, v_zeta;

private:
    void background_stuff(unsigned int);

public:
    model1();
    void run();

};

model1::model1(){
    // ligaments
    ligament
            x0(57.07347, 20.54411, 20.46205, 76.21216, 0.25),
            x1(31.95423,20.54411,36.2549,66.90092,0.25),
            x2(19.46833,15.10836,50.22875,82.05809,0.25),
            x3(14.95728,11.53488,40.95749,121.78992,0.25);
    lig.push_back(x0); lig.push_back(x1); lig.push_back(x2); lig.push_back(x3);
    assert(lig[0].x+lig[1].x+lig[2].x+lig[3].x==1); // check if the sum of all the proportions x = 1
    // muscle
    peroneus.init(6.73575, 500, 6.59942);
    // get data
    read_file(k_file, &data);
    tare = sqrt(pow(data[0], 2));
    // names are taken from the geogebra file
    // backside of the foot
    v_F_Achillessehne.resize(k_len, 0);
    r *= scale;
    // frontside of the foot
    v_F_N.resize(k_len, 0);
    l *= scale;
}

void model1::run() {

    for (unsigned int t_steps = 0; t_steps < k_len; t_steps++) {
        zeta = rad(get_poly_func_value(v_zeta_coef, t_steps));
        mu = rad(get_poly_func_value(v_mu_coef, t_steps));
        peroneus.omega = mu - peroneus.gamma; // angle between u and F_Achillessehne

        v_F_N[t_steps] = F_N = (data[t_steps] + tare) / 2; // divided by two because a human has two feet
        if (F_N < 0) { v_F_N[t_steps] = F_N = 0; } // because there should be no negative force
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
        F = M_A / (lig[0].x * lig[0].r * sin(lig[0].betta) +
                   lig[1].x * lig[1].r * sin(lig[1].betta) +
                   lig[2].x * lig[2].r * sin(lig[2].betta) +
                   lig[3].x * lig[3].r * sin(lig[3].betta));
        // calculate and save Fx (with the function ligament::get_Fx(double))
        save_and_calculate_ligaments(&lig[0], &lig[1], &lig[2], &lig[3], F);

        background_stuff(t_steps); // save and print

    }
    // write to file
    save.save_all_vector(vector<vector<double>*> {&peroneus.v_F, &v_F_N, &v_F_Achillessehne, &v_mu, &v_zeta, &lig[0].v_Fx, &lig[1].v_Fx, &lig[2].v_Fx, &lig[3].v_Fx},
                         vector<string> {"Peroneus.txt", "F_N.txt", "F_Achillessehne.txt", "mu_calculated.txt", "zeta_calculated.txt", "Aponeurosis_plantaris.txt", "Plantare_longum.txt", "Calcaneocuboideum_plantare.txt", "Calcaneonaviculare_plantare.txt"});
}

void model1::background_stuff(unsigned int t_steps) {
// save data
    {
        v_mu.push_back(deg(mu));
        v_zeta.push_back(deg(zeta));
        peroneus.v_F.push_back(peroneus.F);
    }

    // print the output
    print(h_on_floor_check, dt, F_N, F_Achillessehne, lig[0].Fx, peroneus.F, t_steps);
}

int main() {
    calculate_angles_from_coordinates();
    model1 model;
    model.run();
}
