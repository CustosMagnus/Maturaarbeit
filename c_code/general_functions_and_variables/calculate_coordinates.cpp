#include "calculate_coordinates.h"

void calculate_angles_from_coordinates() {
    ofstream zeta_file("./c_results/calc_from_coord/angle_zeta.txt");
    ofstream mu_file("./c_results/calc_from_coord/angle_mu.txt");
    const string f_name = "py_results/coords.txt";
    string txt;
    int j = 0;
    int j_skipped = 0;
    const string delim = " ";
    const unsigned int f_len = file_length(f_name);
    const unsigned int number_of_coordinate_blocks = f_len / 5;
    double ar_zeta[number_of_coordinate_blocks];
    double ar_mu[number_of_coordinate_blocks];
    int ar[f_len / 5 * 4][2]; // number of x,y coordinates
    ifstream file(f_name);
    while (getline(file, txt)) {
        if (j % 5 == 0) {
            j++;
            j_skipped++; // to lower i in ar[i]
            continue;
        }
        size_t pos;
        pos = txt.find(delim);
        ar[j - j_skipped][0] = stoi(txt.substr(0, pos));
        txt.erase(0, pos + delim.length());
        ar[j - j_skipped][1] = stoi(txt);
        j++;
    }
    for (unsigned int i = 0; i < number_of_coordinate_blocks; i++) {
        /*
        picture is x = 640 pixel, y = 360 pixel big
        origin of the pixel is from top left growing to the bottom right
        To change the origin to the bottom left all the y-values are subtracted from the y_size,
        which is defined below.
        */
        const unsigned int y_size = 360;
        /*
        turn so far that m_1,2 = line(Messpunkt1, Messpunkt2) is collinear with l1
        turn by -> (-41.73° + -129.43°) = -171.16°
        */
        const double turn_angle_l1 = -52.08-119.08; // dorsum of the foot
        const double turn_angle_r0 = -52.08; // heel
        // Messpunkt1
        double m1[] = {static_cast<double>(ar[i * 4][0]), static_cast<double>(y_size - ar[i * 4][1])};
        // Messpunkt2
        double m2[] = {static_cast<double>(ar[i * 4 + 1][0]), static_cast<double>(y_size - ar[i * 4 + 1][1])};
        // directional vector |m2,m1|
        double r1_2[] = {m2[0] - m1[0], m2[1] - m1[1]};
        /*
        x' = x*cos(alpha) - y*sin(alpha)
        y' = x*sin(alpha) + y*cos(alpha)
         */
        // turn r1_2 so that it is collinear with l1
        double r_l1[] = {r1_2[0] * cos(rad(turn_angle_l1)) - r1_2[1] * sin(rad(turn_angle_l1)),
                         r1_2[0] * sin(rad(turn_angle_l1)) + r1_2[1] * cos(rad(turn_angle_l1))};
        // turn r1_2 so that it is collinear with r0
        double r_r0[] = {r1_2[0] * cos(rad(turn_angle_r0)) - r1_2[1] * sin(rad(turn_angle_r0)),
                         r1_2[0] * sin(rad(turn_angle_r0)) + r1_2[1] * cos(rad(turn_angle_r0))};
        // Messpunkt3
        double m3[] = {static_cast<double>(ar[i * 4 + 2][0]), static_cast<double>(y_size - ar[i * 4 + 2][1])};
        // Messpunkt4
        double m4[] = {static_cast<double>(ar[i * 4 + 3][0]), static_cast<double>(y_size - ar[i * 4 + 3][1])};
        // directional vector |m3,m4|
        double r3_4[] = {m4[0] - m3[0], m4[1] - m3[1]};
        // angle between r_F_N = [0,1] and l1 (r_F_N is a directional vector perpendicular to the floor)
        double r_F_N[] = {0, 1};
        /*
        angle between two vectors
        alpha = arccos((a*b)/(|a|*|b|))
        */
        // angle at the F_N force
        double zeta = acos((r_l1[0] * r_F_N[0] + r_l1[1] * r_F_N[1]) /
                           (sqrt(pow(r_l1[0], 2) + pow(r_l1[1], 2)) * sqrt(pow(r_F_N[0], 2) + pow(r_F_N[1], 2))));
        // angle at the Achilles tendom
        double mu = acos((r_r0[0] * r3_4[0] + r_r0[1] * r3_4[1]) /
                         (sqrt(pow(r_r0[0], 2) + pow(r_r0[1], 2)) * sqrt(pow(r3_4[0], 2) + pow(r3_4[1], 2))));

        // write into a file, so it is easier to access the data by hand, and also it's awful to return arrays in c++

        zeta = sqrt(pow(deg(zeta) - 180,
                        2)); // zeta now in degree and being transformed into the angle marked in the geogebra file and made positive
        mu = 180 -
             deg(mu); // mu now in degree and being transformed into the angle marked in the geogebra file (adjacent angle)

        zeta_file << zeta << "\n";
        ar_zeta[i] = zeta;
        mu_file << mu << "\n";
        ar_mu[i] = mu;
    }
    zeta_file.close();
    mu_file.close();
}
