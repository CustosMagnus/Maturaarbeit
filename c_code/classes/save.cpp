#include "save.h"

// s_vec Class
void s_vec::save_vector(vector<double> &vec, const string name) {
    ofstream file(("c_results/" + name));
    for (auto i: vec) {
        file << i << "\n";
    }
    file.close();
}

void s_vec::save_all_vector(vector<vector<double>*> vec_val, vector<string> vec_name){
    for (int i = 0; i < vec_name.size(); i++){
        save_vector(*vec_val[i], vec_name[i]);
    }
}