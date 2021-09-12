#include "output_wave_alg_solution.hpp"
#include <vector>
#include <iostream>
using namespace std;

void output_wave_alg_solution(const maze_data *maze_data, const vector<point> &path) {
    bool printed = false;
    int printed_chars = 0;
    for (auto &point : maze_data->field) {
        for (auto &elem : path) {
            if (point == elem) {
                cout << "* ";
                printed = true;
                break;
            }
        }
        if (!printed)
            cout << static_cast<int>(point.state) << " ";
        printed_chars++;
        if (printed_chars % maze_data->width == 0) {
            cout << '\n';
        }
        printed = false;
    }
}
