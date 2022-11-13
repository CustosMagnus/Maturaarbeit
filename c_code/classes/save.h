#ifndef CODE_SAVE_H
#define CODE_SAVE_H

#include <vector>
#include <string>
#include <fstream>

using namespace std;

class s_vec {
private:
    void save_vector(vector<double> &, string);
public:
    void save_all_vector(vector<vector<double>*>, vector<string>);
};

#endif //CODE_SAVE_H
