#include "find_stretching_factor.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double find_stre_func() {
    const vector<double> vec{61.466, 8.8842, -1.3562, 0.0677, -0.0016, 2e-5, -7e-8};
    /*
     t == 11 -> Landung             x == 3
     t == 23 -> tiefster punkt      x == ?
     t == 61 -> absprung fertig     x == 48

     delta_t == 61-11 = 50
     delta_x == 48-3 = 45

     50/45 = 10/9 = increment a
     11-3*10/9 = shift b


     2.5e-3 = time_steps of the force plat
     480 = fps of the t6 camera
     a = 0.0025/(1/480) = 1.2
     */
    float t = 11;
    t = 11;
    float x = 3;

    float a = 10.0 / 9;
    float b = 11 - 3 * a;

    float y = a * x + b;

    int n = 0; // (to the power of n)
    double res = 0;
    for (auto i: vec) {
        res += i * pow(t, n);
        n++;
    }
    n = 0; // (to the power of n)
    double res2 = 0;
    for (auto i: vec) {
        res2 += i * pow(y, n);
        n++;
    }
    cout << "fix: " << res << endl << "calculated: " << res2 << endl;
    cout << "y: " << y << endl << "t: " << t << endl;
    return 0;
}