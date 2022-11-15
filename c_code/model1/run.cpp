#include "model1.h"

void model1::run() {
    for (unsigned int t_steps = 0; t_steps < k_len; t_steps++) {
        zeta = rad(get_poly_func_value(v_zeta_coef, t_steps));
        mu = rad(get_poly_func_value(v_mu_coef, t_steps));
        flexor_hallucis_l.omega = flexor_digitorum_l.omega = peroneus.omega = mu - peroneus.gamma; // angle between u and F_Achillessehne

        v_F_N.push_back(F_N = (data[t_steps] + tare) / 2); // divided by two because a human has two feet
        if (F_N < 0) { v_F_N[t_steps] = F_N = 0; } // because there should be no negative force
        /*
         if heel is not on the floor
         zeta = 62.2° -> point where the heel starts to touch the spieth roll
         zeta = 69 the heel is completley putting pressure on the plate
        */
        if (zeta <= rad(69.0)) {
            h_on_floor_check = false;
            M_N = (F_N - disturbance_forces()) * sin(zeta) * l;
        } else { // if heel is on the floor
            if (h_on_floor == 0) {
                h_on_floor = F_N - disturbance_forces();
            }
            h_on_floor_check = true;
            M_N = h_on_floor * sin(zeta) * l;
        }

        v_F_Achillessehne[t_steps] = F_Achillessehne = M_N / (sin(mu) * r);
        M_A = sin(mu) * r * F_Achillessehne;

        // calculate F_ligament which is the sum of all strains in x_n
        F_ligament = (M_A / (lig[0].x * lig[0].r * sin(lig[0].betta) +
                             lig[1].x * lig[1].r * sin(lig[1].betta) +
                             lig[2].x * lig[2].r * sin(lig[2].betta) +
                             lig[3].x * lig[3].r * sin(lig[3].betta)))
                     - flexor_digitorum_l.F - flexor_hallucis_l.F; // these also support the arch

        if (F_ligament<0){F_ligament=0;} // because it can't be negative (maximum negativ value measured without this line was under 0.2N)
        // calculate and save Fx (with the function ligament::get_Fx(double))
        save_and_calculate_ligaments(&lig[0], &lig[1], &lig[2], &lig[3], F_ligament);

        background_stuff(t_steps); // save and print

    }
    // write to file
    save.save_all_vector(vector<vector<double>*> {&flexor_hallucis_l.v_F, &flexor_digitorum_l.v_F ,&peroneus.v_F, &v_F_N, &v_F_Achillessehne, &v_mu, &v_zeta, &lig[0].v_Fx, &lig[1].v_Fx, &lig[2].v_Fx, &lig[3].v_Fx},
                         vector<string> {"Flexor_hallucis_longus.txt", "Flexor_digitorum_longus.txt", "Peroneus.txt", "F_N.txt", "F_Achillessehne.txt", "mu_calculated.txt", "zeta_calculated.txt", "Aponeurosis_plantaris.txt", "Plantare_longum.txt", "Calcaneocuboideum_plantare.txt", "Calcaneonaviculare_plantare.txt"});
}

