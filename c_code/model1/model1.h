#ifndef CODE_MODEL1_H
#define CODE_MODEL1_H

#include "../dependency/dependency.h"
#include "../classes/muscle.h"
#include "../classes/ligament.h"
#include "../classes/save.h"
#include "../general_functions_and_variables/extern_variables.h"
#include "../general_functions_and_variables/common_use_functions.h"


class model1 : general_var{
public:
    // ligaments
    vector<ligament> lig;
    // muscle
    muscle peroneus;
    double F{}; // total force on all Ligaments
    // files
    s_vec save;
    const string k_file = "c_data/data_kraftmessplatte.txt";
    const unsigned int k_len = file_length(k_file);
    // get data
    vector<double> data;
    double tare; // tare = |data[0]|
    // time
    const double dt = 2.5e-3;
    // heel on floor
    double h_on_floor = 0; // Force at the moment the foot touches the floor
    bool h_on_floor_check{};
    // names are taken from the geogebra file
    // backside of the foot
    double F_Achillessehne{};
    double mu{};
    double M_A{};
    vector<double> v_F_Achillessehne, v_mu;
    // frontside of the foot
    double F_N{};
    double zeta{};
    double M_N{};
    vector<double> v_F_N, v_zeta;

private:
    void background_stuff(unsigned int);
    void print(unsigned int);

public:
    model1();
    void run();

    double mechanical_disturbances();
};



#endif //CODE_MODEL1_H
