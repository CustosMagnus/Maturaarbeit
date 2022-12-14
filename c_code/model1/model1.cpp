#include "model1.h"
#include <cmath>

model1::model1(){
    // ligaments
    ligament
            x0(57.07347, 20.54411, 20.46205, 76.21216, "aponeurosis_plantaris"),
            x1(31.95423, 20.54411, 36.25490, 66.90092, "plantare_longum"),
            x2(19.46833, 15.10836, 50.22875, 82.05809, "calcaneocuboideum_plantare"),
            x3(14.95728, 11.53488, 40.95749, 121.78992, "calcaneonaviculare_plantare");
    lig.push_back(x0); lig.push_back(x1); lig.push_back(x2); lig.push_back(x3);
    assert(lig[0].x+lig[1].x+lig[2].x+lig[3].x==1); // check if the sum of all the proportions x = 1
    // muscle
    peroneus.init(6.73575, 6.59942, "peroneus");
    flexor_digitorum_l.init(6.73575, 6.59942, "flexor_digitorum_longus");
    flexor_hallucis_l.init(6.73575, 10.86235, "flexor_hallucis_longus");
    // get data
    read_file(k_file, &data);
    tare = sqrt(pow(data[0], 2));
    // names are taken from the geogebra file
    // backside of the foot
    v_F_Achillessehne.resize(k_len, 0);
}

void model1::print(unsigned int t_steps){
    if (h_on_floor_check) {
        cout << "Ferse ist auf dem Boden" << endl;
    } else {
        cout << "Ferse ist nicht auf dem Boden" << endl;
    }
    cout << "An t=" << dt * t_steps <<
         "\nF_N: " << F_N <<
         "N\nAchillessehne: " << F_Achillessehne <<
         "N\nAponeurosis plantaris: " << lig[0].Fx <<
         "N\nPeroneus: " << peroneus.F <<
         "N\n\n";
}

void model1::background_stuff(unsigned int t_steps) {
    // save data
    {
        v_mu.push_back(deg(mu));
        v_zeta.push_back(deg(zeta));
        peroneus.v_F.push_back(peroneus.F);
        flexor_digitorum_l.v_F.push_back(flexor_digitorum_l.F);
        flexor_hallucis_l.v_F.push_back(flexor_hallucis_l.F);
    }
    // print the output
    //print(t_steps);
}

double model1::mechanical_disturbances() const {
    return (cos(zeta)*F_N);
}

double model1::disturbance_forces() {
    double F_res = 0;
    F_res += mechanical_disturbances();
    F_res += peroneus.calc_F(F_N - mechanical_disturbances(), zeta);
    F_res += flexor_hallucis_l.calc_F(F_N - mechanical_disturbances(), zeta);
    F_res += flexor_digitorum_l.calc_F(F_N - mechanical_disturbances(), zeta);
    if (F_res>=F_N){F_res=F_N;} // because anything else would be unrealistic
    return F_res;
}

